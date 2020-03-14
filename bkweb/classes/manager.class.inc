<?php

class classArrayManager{
	public $arrayVL = array();
	private $tableName = '';

	public function getArray(){
		return $this->arrayVL;
	}

	public function getTable(){
		return $this->tableName;
	}

	public function __construct($table){
		$this->setList($table);
		$this->tableName = $table;
	}

	public function setList($table){

		$sql = "show fields from " . $table;
		$query = Connector::executeQuery($sql, Connector::getDefaultLink());

		while($row = mysql_fetch_object($query)){
			array_push($this->arrayVL, $row->Field);
		}
	}
}

class dtoManager{

            // Change this point!
	private $vars = array();

	public function setVarsArray($array){
		foreach($array as $campo){
			@array_push($this->vars[$campo] = null);
		}

	}

	public function __construct($array=null) {
		$this->setVarsArray($array);
	}

	public function __destruct() {
	}

	public function __get($propName) {
		if (array_key_exists($propName, $this->vars))
			return $this->vars[$propName];
	}

	public function __set($propName, $value) {
		if (array_key_exists($propName, $this->vars))
			$this->vars[$propName] = $value;
	}

            // Change this point!
	public function ttoString($objArray) {

		$array = array();

		foreach($objArray->getArray() as $campo){
			array_push($array, array($campo, $this->$campo));
		}

		return $array;

	}

}

class daoManager{

            // Change this point!
            protected $tableName = ''; // Table Name!

			protected $keyColumnList = ''; // Key Column List!

			protected $anyColumnList = ''; // For Insert Columns!

			protected $setColumnList = ''; // For Update Command!

			protected $allColumnList = ''; // For Cursor Command (Select)!

			protected $array_list;

			protected $vars = array("link" => null, "pageSize" => 12, "pageNumber" => -1, "pageCount" => -1);

			protected $result = null;

			public function __construct($objArray) {
				$this->tableName = $objArray->getTable();
				$this->array_list = $objArray->getArray();
			}

			public function __destruct() {
				$this->close();
			}

			public function __get($propName) {
				if (array_key_exists($propName, $this->vars))
					return $this->vars[$propName];
			}

			public function __set($propName, $value) {
				if (array_key_exists($propName, $this->vars))
					$this->vars[$propName] = $value;
			}
			public function cdAlternativo($id_cadastro){



				$sql = "UPDATE tab_cliente SET cd_alternativo = 'CLI-ES" . $id_cadastro . "' WHERE id_cliente = ".$id_cadastro;

				$result = Connector::executeQuery( $sql, Connector::getDefaultLink() );



				$results = mysql_fetch_array($result);

				if($results){

					return true;

				}else{

					return false;

				}

			}
			public function openWhere($where) {



				$statement = "Select * from " . $this->tableName . " where " . $where;



				$this->result = Connector::executeQuery($statement, $this->link);

				$this->calculatePageCount();

				return $statement;

			}

			public function open() {

				$statement = "Select * from " . $this->tableName;

				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			public function openUsuarios() {

				$statement = "Select * from " . $this->tableName . " where id_usuario <> '1'";

				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			public function openCaracteristicaHoroscopo($tabela, $array=null) {

				$statement = "Select ".implode(",", $array[1])." from " . $tabela . " where cod_horoscopo = ".$array[0] ;
				
				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			protected function calculatePageCount() {
				$this->pageCount = mysql_affected_rows() / $this->pageSize;
				if(mysql_affected_rows() % $this->pageSize > 0)
					$this->pageCount = ceil($this->pageCount);
				$this->pageNumber = 1;
			}

            // Change this point!
			protected function getObject($row) {

				$obj = new dto($this->array_list);

				foreach($this->array_list as $campo){

					$obj->$campo = (isset($row->$campo)) ? $row->$campo : FALSE;
				}
				return $obj;
			}


			protected function refreshData() {
				$pageNumber = $this->pageNumber;
				$this->open();
				$this->pageNumber = $pageNumber;
			}

			protected function getData() {
				$array = array();
				$i = 0;
				while (($row = mysql_fetch_object($this->result)) && ($i < $this->pageSize)) {
					$array[$i] = $this->getObject($row);
					$i++;
				}
				return $array;
			}

			public function firstPage() {
				$this->pageNumber = 1;
				return $this->gotoPage($this->pageNumber);
			}

			public function previousPage() {
				if($this->pageNumber > 1)
					$this->pageNumber = $this->pageNumber - 1;
				return $this->gotoPage($this->pageNumber);
			}

			public function nextPage() {
				if($this->pageNumber < $this->pageCount)
					$this->pageNumber = $this->pageNumber + 1;
				return $this->gotoPage($this->pageNumber);
			}

			public function lastPage() {
				$this->pageNumber = $this->pageCount;
				return $this->gotoPage($this->pageNumber);
			}


			public function gotoPage($pageNumber) {
				if($pageNumber < 1) $pageNumber = 1;
				if($pageNumber > $this->pageCount) $pageNumber = $this->pageCount;
				$recordNumber = 0;
				if($this->pageCount > 0) {
					$recordNumber = ($pageNumber - 1) * $this->pageSize;
					mysql_data_seek($this->result, $recordNumber);
				}
				return $this->getData();
			}


			public function refreshPage() {
				return $this->gotoPage($this->pageNumber);
			}

			public function getColumnList($array) {
				$lista = false;
				foreach($array as $campo){
					$lista .= $campo . ", ";
				}

				return substr($lista, 0, strlen($lista)-2);
			}

			public function updateOrdem($id, $ordinal) {
				$sql = "UPDATE tab_foto SET cd_ordem='" . $ordinal . "' WHERE id_foto='" . $id . "'";
				Connector::executeQuery($sql, Connector::getDefaultLink());
			}

			public function openFotos($tabela, $array=null) {
				$statement = "SELECT * FROM " . $tabela . " WHERE cd_produto='" . $array[0] . "'";
				$statement .= " ORDER BY cd_ordem";

				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			public function criarPasta($nm_pasta, $cd_pasta){
				$statement = "INSERT INTO tab_datafiles
				(nm_datafiles, cd_pasta, cd_tipo, dt_criacao)
				VALUES
				('" . $nm_pasta . "', '" . $cd_pasta . "', '1', now());";

				Connector::executeQuery($statement, $this->link);

				$last_id = Connector::getAllName("tab_datafiles", "MAX(id_datafiles)", "1=1");
				return $last_id;
			}


			public function createFolder($dir) {
				mkdir($dir, 0777, true);
				chmod($dir, 0777);
			}

			public function openPasta($pasta=null, $filtro=null) {

				$statement = "Select * from tab_datafiles where id_datafiles > '0'";
				if($filtro){
					$statement .= " and (nm_datafiles like '%" . $filtro . "%')";
				}else{
					if($pasta){
						$statement .= " and cd_pasta = '" . $pasta . "'";
					}else{
						$statement .= " and cd_pasta = '0'";
					}
				}

				$statement .= " order by cd_tipo asc, nm_datafiles asc";

				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			public function openTree() {

				$statement = "Select * from " . $this->tableName . " where cd_tipo='1' and cd_pasta='0' order by cd_pasta, nm_datafiles";

				$this->result = Connector::executeQuery($statement, $this->link);
				$this->calculatePageCount();
				return $statement;
			}

			public function getArvores($id_datafiles, $selected=null){
				$nm_datafiles = Connector::getAllName("tab_datafiles", "nm_datafiles", "id_datafiles='" . $id_datafiles . "'");

				$statement = "Select * from tab_datafiles where cd_pasta='". $id_datafiles ."' and cd_tipo='1' order by nm_datafiles";
				$query = Connector::executeQuery($statement, $this->link);
				$num = mysql_num_rows($query);

				$linha = "";

				$linha .= ('{ icon: "images/folder.png", label: "' . $nm_datafiles . '", id:' . $id_datafiles);

				$sPasta = Connector::getPastaArv($selected);

				$sPastas = explode("|", $sPasta);

				for($a=0; $a < count($sPastas); $a++){

					if($sPastas[$a] != ""){
						if($id_datafiles == $sPastas[$a]){
							$linha .= (", expanded: true, selected: true");
						}
					}
				}



				if($num > 0){
					$linha .= (', items: [');

					while($ln = mysql_fetch_array($query)){

						$linha .= $this->getArvores($ln["id_datafiles"], $selected);

					}

					$linha .= ('],');
				}

				$linha .= (' },');

				return $linha;
			}


			public function insertURL($url, $table, $id_table) {
				$url_padrao = $url;
				$statement = false;
				$cont = Connector::numRegistro("tab_url", "url_padrao='" . $url . "'");

				if($cont > 0) $url .= "-".($cont+1);

				$statement = "INSERT INTO tab_url (nm_url, url_padrao, nm_tabela, id_tabela)
				VALUES ('" . $url . "', '" . $url_padrao . "', '" . $table . "', '" . $id_table . "')";
				Connector::executeQuery($statement, $this->link);

				return $statement;
			}

			public function uploadURL($url, $table, $id_table) {
				$url_padrao = $url;
				$statement = false;
				$cont = Connector::numRegistro("tab_url", "url_padrao='" . $url . "'");
				$url_atual = Connector::getAllName("tab_url", "url_padrao","nm_tabela='" . $table . "' AND id_tabela='" . $id_table . "'");

				$exist = Connector::numRegistro("tab_url", "nm_tabela='" . $table . "' AND id_tabela='" . $id_table . "'");

				if($cont > 0)$url .= "-".($cont+1);

				if($url_atual != $url_padrao && $exist > 0){
					$statement = "UPDATE tab_url SET nm_url = '" . $url . "', url_padrao = '" . $url_padrao . "'
					WHERE id_tabela = '" . $id_table . "' AND nm_tabela = '" . $table . "'";
					Connector::executeQuery($statement, $this->link);
				}

				if($exist == 0){
					$statement = "INSERT INTO tab_url (nm_url, url_padrao, nm_tabela, id_tabela)
					VALUES ('" . $url . "', '" . $url_padrao . "', '" . $table . "', '" . $id_table . "')";
					Connector::executeQuery($statement, $this->link);
				}

				return $statement;
			}

            // Change this point!
			public function insert(dto $obj) {

				$this->anyColumnList = $this->getColumnList($this->array_list);

				$statement = SQL::getInsertStatement($this->tableName, $this->anyColumnList);

				foreach($this->array_list as $campo){
					if( is_integer( $obj->$campo ) )	
						$statement = SQL::setInteger($statement, $campo, $obj->$campo);

					elseif( is_double( $obj->$campo ) )	
						$statement = SQL::setDouble($statement, $campo, $obj->$campo);

					elseif( strlen( $obj->$campo ) == 0 )	
						$statement = SQL::setNull($statement, $campo);

					else	
						$statement = SQL::setString($statement, $campo, str_replace('"', "'", trim($obj->$campo)));
				}

				Connector::executeQuery($statement, $this->link);
				$last_id = mysql_insert_id();

				$this->refreshData();

				return $last_id;
			}

            // Change this point!
			public function update(dto $obj, $coln = null) {

				if(isset($coln)){
					$this->setColumnList = $this->getColumnList($coln);
				}else{
					$this->setColumnList = $this->getColumnList($this->array_list);
				}
				$this->keyColumnList = $this->getKeyColumnList($this->tableName);

				$statement = SQL::getUpdateStatement($this->tableName, $this->setColumnList, $this->keyColumnList);

				foreach($this->array_list as $campo){						   
					if( is_integer( $obj->$campo ) )	
						$statement = SQL::setInteger($statement, $campo, $obj->$campo);

					elseif( is_double( $obj->$campo ) )	
						$statement = SQL::setDouble($statement, $campo, $obj->$campo);

					elseif( strlen( $obj->$campo ) == 0 )	
						$statement = SQL::setNull($statement, $campo);

					else	
						$statement = SQL::setString($statement, $campo, str_replace('"', "'", trim($obj->$campo)));

				}
				
				Connector::executeQuery($statement, $this->link);
				$this->refreshData();
				return $statement;
			}

            // Change this point!
			public function delete($codigo) {

				$this->keyColumnList = $this->getKeyColumnList($this->tableName);

				$statement = SQL::getDeleteStatement($this->tableName, $this->keyColumnList);
				$statement = SQL::setInteger($statement, $this->keyColumnList, $codigo);
				Connector::executeQuery($statement, $this->link);
				$this->refreshData();
				return $statement;
			}

            // Change this point!
			public function locate($codigo) {
				
				$this->keyColumnList = $this->getKeyColumnList($this->tableName);
				$this->allColumnList = $this->getColumnList($this->array_list);


				$statement = SQL::getLocateStatement($this->tableName, $this->allColumnList, $this->keyColumnList);

				$statement = SQL::setInteger($statement, $this->keyColumnList, $codigo);
				

				$query = Connector::executeQuery($statement, $this->link);
				if($row = mysql_fetch_object($query)) {
					return $this->getObject($row);
				}
				return null;
			}


			public static function execute($tabela, $metodo, $array = null, $campo=null) {

				$tabela = "tab_" . $tabela;
				$metodo = "open" . $metodo;
						
				$objArray = new classArray($tabela);

				if(count($campo) > 0){
					foreach($campo as $id=>$valor){
						array_push($objArray->arrayVL, $valor);
					}
				}

				$objs = new dao($objArray);
				$objs->link = Connector::getDefaultLink();
				

				$objs->$metodo($tabela, $array);

				$obj = $objs->selectAll();
					
				return $obj;
			}

			public function setExport($array) {

				$arrayExport = array();
				$arrayNome = array();
				$arrayCampo = array();
				$arrayFuncao = array();

				foreach($array as $arrays){
					array_push($arrayNome, $arrays[0]);
				}

				foreach($array as $arrays){
					array_push($arrayCampo, $arrays[1]);
				}

				foreach($array as $arrays){
					array_push($arrayFuncao, $arrays[2]);
				}

				foreach($this->array_list as $campo){

					if(is_int($posicaoArray = array_search($campo, $arrayCampo))){

						if($arrayNome[$posicaoArray]){
							$nome = $arrayNome[$posicaoArray];
						}else{
							list($prefixo, $nome) = explode("_", $campo);
						}

						if($arrayFuncao[$posicaoArray])
							$funcao = $arrayFuncao[$posicaoArray];
						else
							$funcao = "";

						array_push($arrayExport, array(ucwords($nome), $campo, $funcao));

					}else{
						list($prefixo, $nome) = explode("_", $campo);
						array_push($arrayExport, array(ucwords($nome), $campo, ''));
					}
				}

				return $arrayExport;

			}

			public function getKeyColumnList($table){
				$sql = "SHOW INDEX FROM " . $table . " WHERE Key_name = 'PRIMARY'";

				$query = Connector::executeQuery($sql, Connector::getDefaultLink());
				$lista = false;
				while($row = mysql_fetch_object($query)){
					$lista .= $row->Column_name . ", ";
				}

				return substr($lista, 0, strlen($lista)-2);
			}


			public function selectAll() {
				$array = array();

				if($this->pageCount > 0) {
					mysql_data_seek($this->result, 0);
					$i = 0;

					while ($row = mysql_fetch_object($this->result)) {
						$array[$i] = $this->getObject($row);
						$i++;
					}
				}

				return $array;
			}


			public function setNumberObjects($statement, $link){
				return mysql_num_rows(Connector::executeQuery($statement, $link));
			}

			public function getDeleteInformation(){
				$this->keyColumnList = $this->getKeyColumnList($this->tableName);
				return $this->tableName . "|" . $this->keyColumnList;
			}

			public function close() {
				try {
					if($this->result != null)
						mysql_free_result($this->result);
				} catch(Exception $ex) {
				}
				$this->link = null;
			}

			public function getValidate( $nm_login, $nm_senha, $local=false ){
				
				$allColumnList = 'id_usuario, cd_nivel, nm_usuario, nm_email';

				if($local){$keyColumnList = 'nm_login, cd_status';}else{$keyColumnList = 'nm_login, nm_senha, cd_status';}
				
				$statement = SQL::getLocateStatement( $this->tableName , $allColumnList, $keyColumnList );
				
				$statement = SQL::setString( $statement, 'nm_login', mysql_real_escape_string( $nm_login ) );
				if(!$local){$statement = SQL::setString( $statement, 'nm_senha', Functions::Mcrypt( $nm_senha ) );}
				$statement = SQL::setInteger( $statement, 'cd_status', 1 );

				$query = Connector::executeQuery( $statement, Connector::getDefaultLink() );
				
				if($row = mysql_fetch_object($query)) {
					@session_start();	
					$_SESSION["user_code"] 		= ( $row->id_usuario > 0 ) ? (int)$row->id_usuario : FALSE;
					$_SESSION["user_level"] 	= ( $row->cd_nivel > 0 ) ? (int)$row->cd_nivel : FALSE;
					$_SESSION["user_name"] 		= ( strlen($row->nm_usuario) > 0 ) ? $row->nm_usuario : FALSE;
					$_SESSION["user_email"] 	= ( strlen($row->nm_email) > 0  ) ? $row->nm_email : FALSE;
					
					return true;
				}
				
				return false;
			}

            // Change this point!
			public function __toString() {
				return "dao Class";
			}

		}

		?>
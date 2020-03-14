<?php

if(is_file("api/functions.class.inc"))
	$dir = "";
elseif(is_file("../api/functions.class.inc"))
	$dir = "../";
elseif(is_file("../../api/functions.class.inc"))
	$dir = "../../";
elseif(is_file("../../../api/functions.class.inc"))
	$dir = "../../../";
elseif(is_file("../../../../api/functions.class.inc"))
	$dir = "../../../../";
elseif(is_file("../../../../../api/functions.class.inc"))
	$dir = "../../../../../";
elseif(is_file("../../../../../../api/functions.class.inc"))
	$dir = "../../../../../../";
else
	$dir = "";

require_once($dir . "api/connector.class.inc");
require_once($dir . "api/sql.class.inc");
require_once($dir . "api/functions.class.inc");
require_once($dir . "classes/manager.class.inc");


class classArray extends classArrayManager{}

class dto extends dtoManager{}

class dao extends daoManager{

	public function openLocate($tabela, $array=null) {

		$colunas = ( isset($array[3]) ) ? implode(', ', $array[3]) : '*';

		$statement = "SELECT " . $colunas . " FROM " . $tabela . " WHERE 1=1";

		if(isset($array[0]) && $array[0] > 0)
			$statement .= " AND id_conteudo='" . $array[0] . "'";

		if(isset($array[1]) && $array[1] > 0){
			if(is_array($array[1])){
				$statement .= " AND cd_secao IN(" . implode(",",$array[1]) . ")";
			}else{
				$statement .= " AND cd_secao='" . $array[1] . "'";
			}
		}

		if(isset($array[4])){

			if($array[4] == 'DESC' || $array[4] == 'ASC'){
				$order = $array[4];
			}else{
				$order = 'DESC';
			}
		}

		$statement .= " AND cd_status='1'";
		$statement .= " ORDER BY dt_cadastro " . $order;


		if( isset( $array[2] ) && is_array($array[2]) )
			$statement .= " LIMIT " . (int)$array[2][0] . "," . (int)$array[2][1];

		
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openLocateEquipe($tabela, $array=null) {

		$colunas = ( isset($array[3]) ) ? implode(', ', $array[3]) : '*';

		$statement = "SELECT " . $colunas . " FROM " . $tabela . " WHERE 1=1";

		if(isset($array[0]) && $array[0] > 0)
			$statement .= " AND id_conteudo='" . $array[0] . "'";

		if(isset($array[1]) && $array[1] > 0){
			if(is_array($array[1])){
				$statement .= " AND cd_secao IN(" . implode(",",$array[1]) . ")";
			}else{
				$statement .= " AND cd_secao='" . $array[1] . "'";
			}
		}

		if(isset($array[4])){

			if($array[4] == 'DESC' || $array[4] == 'ASC'){
				$order = $array[4];
			}else{
				$order = 'DESC';
			}
		}

		$statement .= " AND cd_status='1'";
		$statement .= " ORDER BY nm_conteudo " . $order;


		if( isset( $array[2] ) && is_array($array[2]) )
			$statement .= " LIMIT " . (int)$array[2][0] . "," . (int)$array[2][1];

		
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openTaxas($tabela, $array=null) {
		$statement = "Select nr_aliq_icms, nr_aliq_icms_st from " . $tabela . " where cd_uf = '" . $array[0] . "'";
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openItens($tabela, $array=null){
		$statement = "select * from tab_item_pedido where id_pedido = ".$array[0];
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openVideosYoutube($tabela, $array=null) {
		
		$statement = "Select nm_link, nm_descricao from " . $tabela . " where cd_status = 1";
		$statement .= " ORDER BY dt_cadastro DESC";
		if( isset( $array[0] ) && is_array($array[0]) )
			$statement .= " LIMIT " . (int)$array[0][0] . "," . (int)$array[0][1];

		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openProdutos($tabela, $array=null) {
		$colunas = ( isset($array[1]) ) ? implode(', ', $array[1]) : '*';
		
		$statement = "SELECT ". $colunas ." FROM " . $tabela ;
		$statement .= " WHERE cd_status='1'";
	
		if(isset($array[0]) && $array[0] != ''){
			$statement .= " AND id_produto = " . $array[0];
		}
		
		if( isset( $array[3] ) && is_array($array[3]) )
			$statement .= " LIMIT " . (int)$array[3][0] . "," . (int)$array[3][1];

		//echo "<pre>"; print_r($statement); die();
		
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openEndereco($tabela, $array=null) {
		$colunas = ( isset($array[1]) ) ? implode(', ', $array[1]) : '*';
		
		$statement = "SELECT ". $colunas ." FROM " . $tabela ;
		if(isset($array[0]) && $array[0] != ''){
			$statement .= " WHERE id_cliente = " . $array[0];
		}
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openCliente($tabela, $array=null) {
		$colunas = ( isset($array[1]) ) ? implode(', ', $array[1]) : '*';
		
		$statement = "SELECT ". $colunas ." FROM " . $tabela ;
		if(isset($array[0]) && $array[0] != ''){
			$statement .= " WHERE id_cliente = " . $array[0];
		}
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openEndCliente($tabela, $array=null) {
		$colunas = ( isset($array[1]) ) ? implode(', ', $array[1]) : '*';
		
		$statement = "SELECT ". $colunas ." FROM " . $tabela ;
		if(isset($array[0]) && $array[0] != ''){
			$statement .= " WHERE id_usuario = " . $array[0];
		}
		
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}

	public function openPedidoDados($tabela, $array=null){
		$statement = "select * from tab_pedido where id_pedido = ".$array[0];
		
		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}
	public function openSysClientes($tabela, $array=null) {

		$statement = "SELECT * FROM tab_cliente WHERE 1";

		if($array[2]){
			$statement .= " AND (
			id_cliente LIKE '%".$array[2]."%' OR
			cd_alternativo LIKE '%".$array[2]."%' OR
			nm_cliente LIKE '%".$array[2]."%' OR
			id_tipo_pessoa LIKE '%".$array[2]."%' OR
			nm_email LIKE '%".$array[2]."%')";
		}

		if($array[1]){
			$pg = (($array[1]-1) * 50);
			$statement .= " ORDER BY id_cliente ASC LIMIT ".$pg.",50";
		}

		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}

	public function getValidateSite( $nm_login, $nm_senha ){

		$allColumnList = 'id_usuario, nm_usuario';
		$keyColumnList = 'nm_login, nm_senha, cd_status';

		$statement = SQL::getLocateStatement( $this->tableName , $allColumnList, $keyColumnList );

		$statement = SQL::setString( $statement, 'nm_login', mysql_real_escape_string( $nm_login ) );
		$statement = SQL::setString( $statement, 'nm_senha', Functions::Mcrypt( $nm_senha ) );
		$statement = SQL::setInteger( $statement, 'cd_status', 1 );

		$query = Connector::executeQuery( $statement, Connector::getDefaultLink() );

		if($row = mysql_fetch_object($query)) {
			@session_start();	
			$_SESSION["user_code_site"] 	= ( $row->id_usuario > 0 ) ? (int)$row->id_usuario : FALSE;
			$_SESSION["user_name_site"] 	= ( strlen($row->nm_usuario) > 0 ) ? $row->nm_usuario : FALSE;

			return true;
		}

		return false;
	}
	public function openSignoList($tabela, $array=null) {

		if(isset($array[1]) != null){
			$where = ' WHERE id = ' . $array[1];
		}else{
			$where = '';
		}
		$statement = "SELECT ". implode(',', $array[0])." FROM " . $tabela . $where;
		

		$this->result = Connector::executeQuery($statement, $this->link);

		$this->calculatePageCount();

		return $statement;
	}

	

	public function openArquivos($tabela, $array=null) {

		$colunas = 'nm_arquivo, nm_caminho, nm_tipo, dt_cadastro';

		$statement = "SELECT " . $colunas . " FROM " . $tabela . " WHERE 1=1";
		if($array[1] == 1){
			$statement .= " AND id_usuario IN (1)";
		} else {
			$statement .= " AND id_usuario IN (" . $array[0] . ")";
		}
		$statement .= " AND cd_status=1";
		$statement .= " ORDER BY dt_cadastro DESC";


		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}

	public function openArquivosAdm($tabela, $array=null) {

		$statement = "SELECT * FROM " . $tabela . " WHERE id_usuario=" . $array;

		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}

	public function openBusca($tabela, $array=null) {

		$colunas = ( isset($array[1]) ) ? implode(', ', $array[1]) : '*';

		$statement = "SELECT " . $colunas . " FROM " . $tabela . " WHERE 1=1";
		$statement .= " AND cd_status=1";
		$statement .= " AND cd_idioma='".lg."'";

			// Tratamento busca inteligente

		if( strlen($array[0]) > 0 ){
			$procurar = $array[0];
			$procurar = explode(' ',$procurar);

			$query_parts = array();
			foreach ($procurar as $val) {
				$query_parts[] = "'%".mysql_real_escape_string($val)."%'";
			}

			$procurarTitulo = implode(' AND nm_conteudo LIKE ', $query_parts);
			$procurarResumo = implode(' AND tx_resumo LIKE ', $query_parts);
			$procurarDesc = implode(' AND tx_descricao LIKE ', $query_parts);
			$statement .= ' AND ((nm_conteudo LIKE '.$procurarTitulo.') OR (tx_resumo LIKE '.$procurarResumo.') OR (tx_descricao LIKE '.$procurarDesc.'))';
		}

			// --- fim tratamento

			//$statement .= " AND (nm_conteudo LIKE '%" . $array[0] . "%'";
			//$statement .= " OR tx_resumo LIKE '%" . $array[0] . "%'";
			//$statement .= " OR tx_descricao LIKE '%" . $array[0] . "%'";
		$statement .= " ORDER BY dt_cadastro DESC";

		$this->result = Connector::executeQuery($statement, $this->link);
		$this->calculatePageCount();
		return $statement;
	}

}

?>
<?php
error_reporting(0);
define('SERVIDOR',

	$_SERVER['SERVER_NAME'] == '127.0.0.1' or

	$_SERVER['SERVER_NAME'] == 'localhost' or

	$_SERVER['SERVER_NAME'] == '192.168.2.145' or

	$_SERVER['SERVER_NAME'] == 'odin');



if(SERVIDOR){

	define ('HTTP_HOST', 'http://'.$_SERVER['HTTP_HOST'].'/');

	$odin = true;

}

else{

	define ('HTTP_HOST', 'http://'.$_SERVER['HTTP_HOST'].'/novo/');

	$odin = false;

}

class Connector {



	private function __construct() {

	}



	public static function getDefaultLink() {

		/* Inicio Copia URL Amigavel */

		if(SERVIDOR){

			$hostname = 'localhost';

			$username = 'dmsnet';

			$password = '1234';

			$database = 'contionl_site';

		}else{

			$hostname = 'localhost';

			$username = 'contionl_site';

			$password = 'contionline@2018#';

			$database = 'contionl_site';

		}

		/* Fim Copia URL Amigavel */

		return self::getLink($hostname, $username, $password, $database);

	}



	public static function getLink($hostname, $username, $password, $database) {



		$link = mysql_connect($hostname, $username, $password)

		or die('Não foi possível conectar: ' . mysql_error());

		mysql_set_charset('utf8',$link);



		mysql_select_db($database)

		or die('Não foi possível selecionar o banco da dados ' . $database);

		return $link;

	}



	public static function executeQuery($query, $link) {

		$result = mysql_query($query);

		if (!$result)

			die('Query inválida: ' . mysql_error());

		return $result;

	}



	public static function getAllName($table, $columnName, $condition){



		$statement = "Select $columnName from $table where $condition";

		$query = self::executeQuery($statement, self::getDefaultLink());

		if($row = mysql_fetch_object($query)) {

			return $row->$columnName;

		}

		return null;

	}



	public static function getPasta($cd_pasta=null){



		$caminho = false;

		$pasta = false;



		if($cd_pasta){

			$caminho .= "|" . self::getAllName("tab_datafiles", "nm_datafiles", "id_datafiles='" . $cd_pasta . "'") . "|";

			$pasta = self::getAllName("tab_datafiles", "cd_pasta", "id_datafiles='" . $cd_pasta . "'");



			if($pasta > "0"){

				$caminho .= self::getPasta($pasta);

			}

		}



		return trim(self::getNameFolders($caminho));





	}



	public static function getNameFolders($array=null){



		$lista = "";

		$list = explode("|", $array);



		for($n=count($list); $n >= 0; $n--){

			if($list[$n] != ""){

				$lista .= $list[$n] . "/" ;

			}

		}

		return str_replace("//", "/", $lista);

	}



	public static function getPastaArv($cd_pasta, $dir=null){



		$dir .= "|" . $cd_pasta;



		$pasta = self::getAllName("tab_datafiles", "cd_pasta", "id_datafiles = '" . $cd_pasta . "'");



		if($pasta > 0)

			self::getPastaArv($pasta, $dir);



		return $dir;

	}



	public static function makeSelect($tabela, $campo_valor, $campo_nome, $selecionado=null, $condicao=null, $ordenacao=null, $optSeleciona=null){



		$lista = false;



		if($condicao)

			$condicao = " where " . $condicao;



		if($ordenacao)

			$ordenacao = " order by " . $ordenacao;



		$statement = "Select $campo_valor, $campo_nome from $tabela $condicao $ordenacao";



		$query = self::executeQuery($statement, self::getDefaultLink());



		if($optSeleciona != 1){

			$lista .= "<option value=''> - Selecione - </option>";

		}



		while($row = mysql_fetch_array($query)) {



			if($row[$campo_valor] == $selecionado){

				$selected = "selected='selected'";

			}else{

				$selected = "";

			}



			$lista .= "<option value='" . $row[$campo_valor] . "' " . $selected . ">" . $row[$campo_nome] . "</option>";



		}

		return $lista;

	}





	public static function getSecao($secao){



		$id = Connector::getAllName("tab_conteudo", "id_conteudo", "cd_secao='" . $secao . "' and cd_status='1' ORDER BY dt_cadastro DESC");

		$nm_url = Connector::getAllName("tab_url", "nm_url", "nm_tabela='tab_conteudo' and id_tabela='" . $id . "'");

		if( strlen($nm_url) > 0)

			return HTTP_HOST . $nm_url;

		else

			return HTTP_HOST . '';

	}



	public static function getUrl($tabela, $id){

		$nm_url = Connector::getAllName("tab_url", "nm_url", "nm_tabela='" . $tabela . "' and id_tabela='" . $id . "'");

		if( strlen($nm_url) > 0)

			return HTTP_HOST . $nm_url;

		else

			return HTTP_HOST . '';

	}



	public static function numRegistro($table, $condition) {



		$statement = "Select * from $table where $condition";

		$query = self::executeQuery($statement, self::getDefaultLink());



		if($row = mysql_num_rows($query)) {

			return $row;

		}

		return null;

	}

	/* Fim Copia URL Amigavel */



	public static function closeLink($link) {

		try {

			mysql_close($link);

		} catch(Exception $ex) {

		}

	}

}

?>
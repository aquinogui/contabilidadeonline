<?php
if (version_compare(phpversion(), '5.5.0', '<')) {
    // Versao menor que 5.5
} else {
	date_default_timezone_set('America/Sao_Paulo'); //or change to whatever timezone you want
}

error_reporting(E_WARNING);
session_start();

	require_once("classes/class.inc");

	$url_cod = (isset($_REQUEST['cod'])) ? str_replace("'","",$_REQUEST['cod']) : '';
	$url_nm_secao = explode('/', str_replace("'","",$url_cod));

	// -- variaveis de URL amigavel --

	// ultimo valor separado por barras
	$urlCont = $url_nm_secao[count($url_nm_secao)-1];
	// penultimo valor separado por barras
	$urlTipo = $url_nm_secao[count($url_nm_secao)-2];
	
	// ---------------------------------

	$url_id = Connector::getAllName("tab_url", "id_tabela", "nm_url='" . $urlCont . "'");
	$url_tabela = Connector::getAllName("tab_url", "nm_tabela", "nm_url='" . $urlCont . "'");

	$url_secao = Connector::getAllName("tab_conteudo", "cd_secao", "id_conteudo='" . $url_id . "'");
	$url_indice = Connector::getAllName("tab_secao", "cd_indice", "id_secao='" . $url_secao . "'");
	$pagInterna = "modelo.php";

	if($url_tabela == "tab_conteudo" && $url_nm_secao[0] != 'galeria-de-fotos'){
		$_GET["codigo"] = $url_id;
		include_once $pagInterna;
	}elseif($url_tabela == "tab_galeria"){
		$_GET["codigo"] = $url_id;
		include_once "galeria.php";
	}else{

		if(isset($url_nm_secao[0]) && $url_nm_secao[0] == '' || $url_nm_secao[0] == 'index'){
				include_once("home.php");
		}elseif($url_nm_secao[0] != ''){
			$paginas = array('contato','index','home');

			if(isset($url_nm_secao[0]) && in_array($url_nm_secao[0], $paginas)){
				include_once $url_nm_secao[0].".php";
			} else if(isset($url_nm_secao[0]) && $url_nm_secao[0] == 'galeria-de-fotos'){
				include_once "albuns.php";
			} else if(isset($url_nm_secao[0]) && $url_nm_secao[0] == 'pagina-nao-encontrada'){
				$_GET["codigo"] = "404-not-found";
				include_once $pagInterna;
			} else {
				$_GET["codigo"] = "404-not-found";
				include_once $pagInterna;
			}
		} else {

			include_once("home.php");
		}

	}

?>
<?php
require_once("functionsmanager.class.inc");

class Functions extends FunctionsManager{

	public static function getUrl($x){
		return Connector::getUrl("tab_conteudo", $x);
	}

	public static function getAreaArquivo($x){

		switch($x){
			case 1: $retorno = "Trabalhistas"; break;
			case 2: $retorno = "Administrativo / Financeiro"; break;
			case 3: $retorno = "Contabilidade / Fiscal"; break;
			default: $retorno = "N&atilde;o especificado"; break;
		}

		return $retorno;
	}
	public static function getUrlProduto($x){
		return Connector::getUrl("tab_produto", $x);
	}
public static function formatDataHora($x){



		$retorno = date("d/m/Y - h:i:s", strtotime($x));



		return $retorno;

	}
	public static function getReais($x){

		if($x){

			$retorno = str_replace(".",",",$x);	

			return "R$ ".$retorno;	

		} else {

			return "Sem valor";

		}



	}
	public static function getSubMenu($x){
		switch($x){
			case 14:$retorno = 13; break;
			case 5: $retorno = 9;  break;
			case 6: $retorno = 10; break;
			case 7: $retorno = 11; break;
			case 8: $retorno = 12; break;
			case 9: $retorno = 9;  break;
			case 10: $retorno = 10; break;
			case 11: $retorno = 11; break;
			case 12: $retorno = 12; break;
			case 13:$retorno = 13; break;
			case 16:$retorno = 18; break;
			case 18:$retorno = 18; break;

			default: $retorno = ""; break;
		}

		return $retorno;
	}

	public static function getFormContatoInterna($x){

		$astrologia = '
		<input type="text" placeholder="Data de Nascimento:" name="Data_Nascimento" class="form-atend">
		<input type="text" placeholder="Hora de Nascimento:" name="Hora_Nascimento" class="form-atend">
		<input type="text" placeholder="Cidade:" name="Cidade" class="form-atend">
		';
		$astrologia1 = '
		<input type="text" placeholder="Data de Nascimento:" name="Data_Nascimento" class="form-atend">
		<input type="text" placeholder="Endereço:" name="Edereco" class="form-atend">
		<input type="text" placeholder="Cidade:" name="Cidade" class="form-atend">
		';

		switch($x){
			
			case 9: $retorno = array($astrologia, 'Astrologia');  break;
			case 10: $retorno = ''; break;
			case 11: $retorno = ''; break;
			case 12: $retorno = ''; break;
			case 13:$retorno = ''; break;

			default: $retorno = ""; break;
		}

		return $retorno;
	}

	public static function getMonth($x){

		switch($x){
			case 1: $retorno = "Janeiro"; break;
			case 2: $retorno = "Fevereiro"; break;
			case 3: $retorno = "Mar&ccedil;o"; break;
			case 4: $retorno = "Abril"; break;
			case 5: $retorno = "Maio"; break;
			case 6: $retorno = "Junho"; break;
			case 7: $retorno = "Julho"; break;
			case 8: $retorno = "Agosto"; break;
			case 9: $retorno = "Setembro"; break;
			case 10: $retorno = "Outubro"; break;
			case 11: $retorno = "Novembro"; break;
			case 12: $retorno = "Dezembro"; break;

			default: $retorno = "M&ecirc;s n&atilde;o especificado"; break;
		}

		return $retorno;
	}

	public static function getClienteNome($x){

		return (Connector::getAllName("tab_cliente","nm_cliente","id_cliente = ".$x));

	}

	public static function getProdutoNome($x){

		return Connector::getAllName("tab_produto","nm_produto","id_produto = ".$x);

	}

	public static function getStatusPagSeguro($x){



		switch($x){

			case 0: $retorno = "<span> Aguardando pagamento </span>"; break;

			case 1: $retorno = "<span style='color:DarkSlateGrey;'> Aguardando pagamento </span>"; break;

			case 2: $retorno = "<span style='color:CadetBlue;'> Em an&aacute;lise </span>"; break;

			case 3: $retorno = "<span style='color:DarkGreen;'> <strong> Pago </strong> </span>"; break;

			case 4: $retorno = "<span style='color:ForestGreen;'> <strong> Dispon&iacute;vel </strong> </span>"; break;

			case 5: $retorno = "<span style='color:DeepPink;'> Em disputa </span>"; break;

			case 6: $retorno = "<span style='color:Brown;'> Devolvida </span>"; break;

			case 7: $retorno = "<span style='color:Crimson;'> Cancelada </span>"; break;

			case 8: $retorno = "<span style='color:DarkRed;'> Debitado </span>"; break;

			case 9: $retorno = "<span style='color:IndianRed;'> Reten&ccedil;&atilde;o tempor&aacute;ria </span>"; break;

			default: $retorno = "N&atilde;o especificado"; break;

		}



		return $retorno;



	}

public static function tipoPessoa($x){

	

		switch($x){

			case 1: $retorno = "Pessoa Jurídica"; break;

			case 2: $retorno = "Pessoa Física"; break;

			default: $retorno = "Pessoa não especificada"; break;

		}



		return $retorno;

	}
	public static function getHoroscopos($x){

		switch($x){
			case 'aries': $retorno = 1; break;
			case 'touro': $retorno = 2; break;
			case 'gemeos': $retorno = 3; break;
			case 'cancer': $retorno = 4; break;
			case 'leao': $retorno = 5; break;
			case 'virgem': $retorno = 6; break;
			case 'libra': $retorno = 7; break;
			case 'escorpiao': $retorno = 8; break;
			case 'sargitario': $retorno = 9; break;
			case 'capricornio': $retorno = 10; break;
			case 'aquario': $retorno = 11; break;
			case 'peixes': $retorno = 12; break;
			

			default: $retorno = "Signo n&atilde;o especificado"; break;
		}

		return $retorno;
	}


	public static function getNameUpload($name){
		$ext = self::getExtension($name);
		return self::permalink( substr( $name, 0, -( strlen($ext) + 1 ) ) ) . '-' . date('s') . "." . $ext;
	}

	public static function getDepartamento($x){

		switch($x){
			case 1: $retorno = "Cont&aacute;bil"; break;
			case 2: $retorno = "Fiscal"; break;
			case 3: $retorno = "Pessoal"; break;
			case 4: $retorno = "Societ&aacute;rio"; break;
			case 5: $retorno = "Auditoria"; break;
			case 6: $retorno = "Consultoria"; break;
			case 7: $retorno = "Tecnologia"; break;
			case 8: $retorno = "Atendimento Cliente"; break;
			case 9: $retorno = "Comercial"; break;
			case 10: $retorno = "Gerencial"; break;
			default: $retorno = "N&atilde;o especificado"; break;
		}

		return $retorno;
	}

	public static function getExperiencia($x){

		switch($x){
			case 1: $retorno = "Estagio"; break;
			case 2: $retorno = "Primeiro Emprego"; break;
			case 3: $retorno = "At&eacute; 1 ano"; break;
			case 4: $retorno = "At&eacute; 2 anos"; break;
			case 5: $retorno = "At&eacute; 3 anos"; break;
			case 6: $retorno = "At&eacute; 5 anos"; break;
			case 7: $retorno = "Mais de 5 anos"; break;
			default: $retorno = "N&atilde;o especificado"; break;
		}

		return $retorno;
	}

	public static function getEscolaridade($x){

		switch($x){
			case 1: $retorno = "2o. grau incompleto"; break;
			case 2: $retorno = "2o. grau/t&eacute;cnico"; break;
			case 3: $retorno = "Superior incompleto/cursando"; break;
			case 4: $retorno = "Superior"; break;
			case 5: $retorno = "P&oacute;s-graduado ou MBA"; break;
			case 6: $retorno = "Mestrado ou Doutorado"; break;
			default: $retorno = "N&atilde;o especificado"; break;
		}

		return $retorno;
	}


	public static function validaEmail($email){
		$conta = "^[a-zA-Z0-9\._-]+@";
		$domino = "[a-zA-Z0-9\._-]+.";
		$extensao = "([a-zA-Z]{2,4})$";

		$pattern = $conta.$domino.$extensao;

		if (ereg($pattern, $email))
			return true;
		else
			return false;
	}


	public static function getData($x, $tipo=0){

		$ex = explode(' ',$x);
		$x = explode('-',$ex[0]);

		$dia = $x[2];
		$ano = $x[0];

		switch($x[1]){
			case 1: $mes = "JAN"; break;
			case 2: $mes = "FEV"; break;
			case 3: $mes = "MAR"; break;
			case 4: $mes = "ABR"; break;
			case 5: $mes = "MAI"; break;
			case 6: $mes = "JUN"; break;
			case 7: $mes = "JUL"; break;
			case 8: $mes = "AGO"; break;
			case 9: $mes = "SET"; break;
			case 10: $mes = "OUT"; break;
			case 11: $mes = "NOV"; break;
			case 12: $mes = "DEZ"; break;

			default: $mes = "m&ecirc;s"; break;
		}

		if($tipo == 0){

			$mes = substr($mes, 0, 3);
			$retorno = '<strong>'.$dia.'</strong>'.$mes.'/'.$ano.'';


		} else {

			$retorno = $dia.' de '.$mes;

		}
		return $retorno;
	}



}
?>
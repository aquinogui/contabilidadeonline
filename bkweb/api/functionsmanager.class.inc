<?php

	 class FunctionsManager{
		 
	 	public static function limitText($texto, $limit) {

	 		preg_match('/^((?:\X){0,' . $limit . '})/u', $texto, $matches);

	 		return $matches[1] . "...";
	 	}

	 	public static function getHoroscopo( $code ){
	 		$sql = "SELECT nm_horoscopo FROM tab_horoscopos";
	 		$sql .= " WHERE id = " . $code;
	 		$query = Connector::executeQuery( $sql, Connector::getDefaultLink() );

	 		while( $row = mysql_fetch_array( $query ) ){
	 			return $row[0] ;
	 		}
	 	}
		
		public static function selectSecoes( $selected=null ){
			$ln = false;
			
			$sql = "SELECT i.nm_indice, i.id, s.id_secao, s.nm_secao FROM tab_indice i";
			$sql .= " JOIN tab_secao s ON (i.id = s.cd_indice)";
			$sql .= " GROUP BY s.id_secao";
			$sql .= " ORDER BY s.cd_indice ASC, s.nm_secao ASC";
					
			$query = Connector::executeQuery( $sql, Connector::getDefaultLink() );
			$num = (int)mysql_num_rows($query);
			$group = 0;
			$ult = FALSE;
			
			while( $row = mysql_fetch_array( $query ) ){
				$group++;
				
				if( $group == 1 || $ult != $row['id']){ 
					if( $group > 1 ) $ln .= '</optgroup>';
					$ln .= '<optgroup label="' . $row['nm_indice'] . '">'; 
					$ult = $row['id'];
				}
				$select = ( $selected == $row['id_secao'] ) ? ' selected="selected"' : FALSE;
					$ln .= '<option value="' . $row['id_secao'] . '"' . $select . '>' . $row['nm_secao'] . '</option>';
				
				if( $group == $num ) $ln .= '</optgroup>';
			}
			
			return $ln;
	    }

		public static function rteSafe($strText) {
			$tmpString = $strText;

			$tmpString = str_replace(chr(145), chr(39), $tmpString);
			$tmpString = str_replace(chr(146), chr(39), $tmpString);
			$tmpString = str_replace("'", "'", $tmpString);

			$tmpString = str_replace(chr(147), chr(34), $tmpString);
			$tmpString = str_replace(chr(148), chr(34), $tmpString);

			$tmpString = str_replace(chr(10), " ", $tmpString);
			$tmpString = str_replace(chr(13), " ", $tmpString);
			return $tmpString;
		}
		
		public static function Mcrypt($pass){
			$salt = md5('jmaster');
			$codifica = crypt($pass, $salt);
			$codifica = hash('sha256',$codifica);
			
			return $codifica;
		}

	     public static function getExtension($arquivo, $tipo='.*'){

	        preg_match("/\.(" . $tipo . "){1}$/i", $arquivo, $ext);

		   return $ext[1];
		 }

		 public static function getSelected($valor, $opt){
			 if($valor == $opt)
			   return " selected='selected'";
			 else
			   return '';
		 }

		 public static function getChecked($valor, $opt){
			  $lista = explode("|", $opt);
			  for($i=0; $i<count($lista); $i++)
			  {
				  if($lista[$i] == $valor)
				  {
					  return ' checked="checked"';
				  }
				  else{
					  return '';
				  }
			  }
		 }

		 public static function listarPasta($dir, $pasta=null){
				$d = opendir($dir);
				$i = 0;
				$nome = readdir($d);
				while( $nome != false ){
					if(is_dir($nome) && ($pasta != '') && ($nome != '.')){
						$pastas[$i] = $nome;
								$i++;
					}
					$nome = readdir($d);
				}
				return $pastas;
			}

		public static function listarArquivos($dir){
				$d = opendir($dir);
				$i = 0;
				$nome = readdir($d);
				while( $nome != false ){
					if(!is_dir($nome) && ($nome != 'Thumbs.db') ){
						$arquivos[$i] = $nome;
								$i++;
					}
					$nome = readdir($d);
				}
				return $arquivos;
			}

		  public static function get_include_contents($filename) {

			if (is_file($filename)) {
			  ob_start();
			  include $filename;
			  $contents = ob_get_contents();
			  ob_end_clean();
			  return $contents;
			}
			return false;
		  }
		  
		public static function SureRemoveDir($dir, $DeleteMe) {
		
			if(!$dh = opendir($dir)) return;
			
			while (($obj = readdir($dh))) {
				if($obj=='.' || $obj=='..') continue;
				
				if(!unlink($dir.'/'.$obj)) self::SureRemoveDir($dir.'/'.$obj, true);
			}
			
			if ($DeleteMe){
				closedir($dh);
				rmdir($dir);
			}
		}

		 public static function getDataArquivo($arquivo){
			 return date ("d/m/Y H:i:s", filemtime($arquivo));
		 }

		 public static function goPage($page){
			   echo "<script>window.location='" . $page . "'</script>";
		 }

 		 public static function getFormatNumber($valor){
			   return number_format($valor, 2, ",", ".");
		 }

		public static function permalink($str, $enc = "UTF-8"){

			$arr = array('.','´','`','¨','^','~','$','!',',',';',':','?',
			'[','@','#','%','&','*','(',')','_','+','{','}','<','>','/',
			'=','º','ª','¹','²','³','£','¢','¬','§',']','"','”','“','–',"'");
			$str = str_replace($arr, '-', $str);

			$acentos = array(
			'A' => '/À|Á|Â|Ã|Ä|Å/',
			'a' => '/à|á|â|ã|ä|å/',
			'C' => '/Ç/',
			'c' => '/ç/',
			'E' => '/È|É|Ê|Ë/',
			'e' => '/è|é|ê|ë/',
			'I' => '/Ì|Í|Î|Ï/',
			'i' => '/ì|í|î|ï/',
			'N' => '/Ñ/',
			'n' => '/ñ/',
			'O' => '/Ò|Ó|Ô|Õ|Ö/',
			'o' => '/ò|ó|ô|õ|ö/',
			'U' => '/Ù|Ú|Û|Ü/',
			'u' => '/ù|ú|û|ü/',
			'Y' => '/Ý/',
			'y' => '/ý|ÿ/',
			'a.' => '/ª/',
			'-' => '/ |"|ˆ|´|•|“|”|–/',
			'o.' => '/º/'
			);
			$res = preg_replace($acentos, array_keys($acentos),	$str);
			$res = str_replace('----', '-', $res);
			$res = str_replace('---', '-', $res);
			$res = str_replace('--', '-', $res);

			$exp = strrev($res);
			$exp = substr($exp, 0, 1);
			if($exp == '-') $res = substr($res, 0, (strlen($res)-1));

			$res = str_replace('----', '-', $res);
			$res = str_replace('---', '-', $res);
			$res = str_replace('--', '-', $res);

			return strtolower($res);
		}

		 public static function getOnlyNumbers($var){
  		   return preg_replace("/\D/i", '', $var);
 		 }

		 public static function mask($val, $mask){

		   $val = self::getOnlyNumbers($val);

		   $maskared = '';
		   $k = 0;
		   if(strlen($val) > 0){
			   if($mask == 'tel'){
				$cont = strlen($val);
				if($cont == 11){$mask = "(##) #####-####";}
				else{$mask = "(##) ####-####";}
			   }

			   for($i = 0; $i<=strlen($mask)-1; $i++){
				 if($mask[$i] == '#'){
				   if(isset($val[$k]))
					 $maskared .= $val[$k++];
				 }else{
				   if(isset($mask[$i]))
					 $maskared .= $mask[$i];
				 }
			   }
		   }
		   return $maskared;
		}

		public static function formatMySql($dt) {
		  $dt = explode("/", $dt);
          return $dt[2] . "-" . $dt[1] . "-" . $dt[0];
        }

		public static function formatHtml($dt) {
	      $listDt = explode(" ", $dt);
		  $dt = explode("-", $listDt[0]);
		  return $dt[2] . "/" . $dt[1] . "/" . $dt[0];
		}

	 	public static function formatHora($hr) {
	 		$listHr = explode(" ", $hr);
	 		$hr = explode(":", $listHr[1]);
	 		return $hr[0] . ":" . $hr[2];
	 	}

		public static function getDecimal($valor){
		  return str_replace(",", ".", str_replace(".", "", $valor));
		}

		public static function getDateExt(){
					$dia = date('d');
					$mes = date('m');
					$ano = date('Y');
					$semana = date('w');

					$mes = self::getMes($mes);
					$semana = self::getSemana($semana);

					return ("$semana, $dia de $mes de $ano");

			}

			public static function getSemana($semana){
				switch ($semana) {

					case 0: $semana = "Domingo"; break;
					case 1: $semana = "Segunda-feira"; break;
					case 2: $semana = "Ter&ccedil;a-feira"; break;
					case 3: $semana = "Quarta-feira"; break;
					case 4: $semana = "Quinta-feira"; break;
					case 5: $semana = "Sexta-feira"; break;
					case 6: $semana = "S&aacute;bado"; break;

					}
					return $semana;
			}

			public static function getMes($mes){
			  switch ($mes){

					case 1: $mes = "Janeiro"; break;
					case 2: $mes = "Fevereiro"; break;
					case 3: $mes = "Mar&ccedil;o"; break;
					case 4: $mes = "Abril"; break;
					case 5: $mes = "Maio"; break;
					case 6: $mes = "Junho"; break;
					case 7: $mes = "Julho"; break;
					case 8: $mes = "Agosto"; break;
					case 9: $mes = "Setembro"; break;
					case 10: $mes = "Outubro"; break;
					case 11: $mes = "Novembro"; break;
					case 12: $mes = "Dezembro"; break;

					}

				return $mes;
			}

			public static function getSimNao($x){
				if($x==0)
				  return "N&atilde;o";
				if($x==1)
				  return "Sim";
			}

			public static function getStatus($status){
		    	if($status == 0)
		     		return "Inativo";
		   		if($status == 1)
		     		return "Ativo";
	     	}

			public static function getEstado($estado){
		      return Connector::getAllName("tab_estado", "nm_estado", "id_estado='" . $estado . "'");
	        }

			public static function getLogradouro($cd_logradouro){
			 if($cd_logradouro == 1){return "Alameda";}
			 if($cd_logradouro == 2){return "Avenida";}
			 if($cd_logradouro == 3){return "Estrada";}
			 if($cd_logradouro == 4){return "Pra&ccedil;a";}
			 if($cd_logradouro == 5){return "Rodovia";}
			 if($cd_logradouro == 6){return "Rua";}
			 if($cd_logradouro == 7){return "Travessa";}
		   }

		   public function getSenha($v){
		     return base64_decode($v);
		   }

		   public function validaCPF($cpf){
				if (strlen($cpf) != 11 || $cpf == '00000000000' || $cpf == '11111111111' || $cpf == '22222222222' || $cpf == '33333333333' || $cpf == '44444444444' || $cpf == '55555555555' || $cpf == '66666666666' || $cpf == '77777777777' || $cpf == '88888888888' || $cpf == '99999999999')
				{
					return false;
				}
				else
				{
					for ($t = 9; $t < 11; $t++) {
						for ($d = 0, $c = 0; $c < $t; $c++) {
							$d += $cpf{$c} * (($t + 1) - $c);
						}

					$d = ((10 * $d) % 11) % 10;

						if ($cpf{$c} != $d) {
							return false;
						}
					}
					return true;
				}
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

		   public static function getEstadoCivil($x){

              switch($x){
				  case "C": $retorno = "Casado(a)"; break;
				  case "D": $retorno = "Divorciado(a)"; break;
				  case "S": $retorno = "Solteiro(a)"; break;
                  case "V": $retorno = "Vi&uacute;vo(o)"; break;
				  default: $retorno = "N&atilde;o especificado"; break;
			  }

			  return $retorno;
		   }

		   public static function getMascaraCep($v){
		     return self::mask($v, "#####-###");
		   }

		   public static function getMascaraTelefone($v){
		     return self::mask($v, "tel");
		   }

		   public static function getMascaraCPF($v){
		     return self::mask($v, "###.###.###-##");
		   }

		   public static function getSecao($x){
			 return Connector::getAllName("tab_secao", "nm_secao", "id_secao='" . $x . "'");
		   }
		   
		   public static function getIndice($x){
			   return Connector::getAllName("tab_indice", "nm_indice", "id='" . $x . "'");
		   }
		   
		   public static function getConfig($x){
			   return trim( Connector::getAllName("tab_config", "nm_valor", "nm_config='" . $x . "'") );
		   }
		   

	 }

?>
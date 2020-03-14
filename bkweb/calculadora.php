<?php include ("includes/inicio.php"); ?>
    <?php include ("includes/header.php"); ?>
<?php

$url_secao = Connector::getAllName("tab_conteudo", "cd_secao", "id_conteudo='" . $_GET['codigo'] . "'");
session_start();
error_reporting(0);
$obj = dao::execute( "conteudo", "Locate", array( str_replace("'","",(int)$_GET['codigo']), str_replace("'","",(int)$_GET['secao']), array(0,1), array( 'id_conteudo', 'nm_description', 'nm_conteudo', 'nm_h1', 'tx_descricao', 'nm_imagem1','nm_imagem2' ) ) );

if($_GET['codigo'] <> "404-not-found"){
  
  if( count($obj) == 0 || ( (int)$_GET['codigo'] == 0 && (int)$_GET['secao'] == 0)  )
    header( "location: " . HTTP_HOST . "pagina-nao-encontrada" );

  if($obj[0]->nm_h1 <> ''){
    $tituloCont = $obj[0]->nm_h1;
  } else {
    $tituloCont = $obj[0]->nm_conteudo;
  }
  $descCont = $obj[0]->tx_descricao;
} else {
  $tituloCont = "P&aacute;gina n&atilde;o encontrada";
  $descCont = "<p>Certifique-se de ter digitado corretamente o endere&ccedil;o.</p>";
}
	if($obj[0]->nm_imagem2 != ''){
		$capa = $obj[0]->nm_imagem2;
	}else{
		$capa = "images/bg2.jpeg";
	}
?>
        <div class="banner-in" style="background-image: url(<?php echo $capa;?>);">
        </div>
        <section id="modelo">
<div class="container">
<h1 class="tit-interna"><?php echo $obj[0]->nm_h1; ?></h1>
</div>
            <div class="container">
                <div class="content-in">
                    <p><?php echo $obj[0]->tx_descricao; ?></p>
                </div>
                
                <sidebar>
                   <!-- <h3>Nossos Serviços</h3>-->
                     <div class="box">
                       <img src="images/abrir-empresa.png" alt="">
                        <h2>Abrir sua empresa</h2>
                        <p>A Contabilidade Online é um escritório de contabilidade que, além de entregar a contabilidade de sua empresa, é especialista em abrir e cuidar de micro e pequenas empresas.</p>
                        <button>Abra sua empresa</button>
                    </div>
                    
                      <div class="box">
                       <img src="images/traga-empresa.png" alt="">
                        <h2 style="color:#626262;">Traga sua empresa</h2>
                        <p>A Contabilidade Online é um escritório de contabilidade que, além de entregar a contabilidade de sua empresa, é especialista em abrir e cuidar de micro e pequenas empresas.</p>
                        <button style="background:#626262;">Traga sua empresa</button>
                    </div>
                </sidebar>
            </div>
        </section>
        <!--FIM CONTENT-->
        <?php include ("includes/footer.php"); ?>
<?php include("includes/inicio.php");?>
<?php
$url_secao = Connector::getAllName("tab_conteudo", "cd_secao", "id_conteudo='" . $_GET['codigo'] . "'");
session_start();
error_reporting(0);
$obj = dao::execute( "conteudo", "Locate", array( str_replace("'","",(int)$_GET['codigo']), str_replace("'","",(int)$_GET['secao']), array(0,1), array( 'id_conteudo', 'nm_description', 'nm_conteudo', 'nm_h1', 'tx_descricao', 'nm_imagem1' ) ) );

if($_GET['codigo'] <> '404-not-found'){
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
?>
<meta name="description" content="<?php if( strlen($obj[0]->nm_description) > 0) echo $obj[0]->nm_description; else echo Functions::getConfig('meta_description');?>">
<meta name="keywords" content="<?php echo Functions::getConfig('meta_keywords');?>">
<title><?php echo Functions::getConfig('title');?> | <?php echo $obj[0]->nm_conteudo;?></title>
<meta name="robots" content="index, follow">

<!-- Add mousewheel plugin (this is optional) -->
<script type="text/javascript" src="library/fancybox/lib/jquery.mousewheel-3.0.6.pack.js"></script>
<!-- Add fancyBox main JS and CSS files -->
<script type="text/javascript" src="library/fancybox/source/jquery.fancybox.js?v=2.1.5"></script>
<link rel="stylesheet" type="text/css" href="library/fancybox/source/jquery.fancybox.css?v=2.1.5" media="screen" />
<link rel="stylesheet" href="css/blueimp.css">

<script type="text/javascript">
  $('.fancybox').fancybox({
   padding: 0,
   helpers: {
    overlay: {
     locked: false
   }
 }
});
</script>


</head>

<body>
  <?php include("includes/header.php");?>

  <section>

    <div class="banner-int" style="background-image: url(<?php echo $obj[0]->nm_imagem1; ?>);">
      <div class="container-int">
        <h1><?php echo $obj[0]->nm_h1; ?></h1>            
      </div>        
    </div>
    


    <div class="container-int">
      <div class="left-cont">
        <p><?php echo $obj[0]->tx_descricao; ?></p>            

      </div>
      <div class="right-cont">
        <?php 

        $getSub = Functions::getSubMenu($url_secao);
         
        if($getSub != ''){
         $subMenu = $getSub;
       }else{
        $subMenu = $_SESSION['submenu'];
      }

      if( $subMenu != ''){
        $obj = dao::execute( "conteudo", "LocateEquipe", array( FALSE, $subMenu , '' , array( 'id_conteudo', 'nm_conteudo', 'nm_h1', 'tx_resumo', 'nm_imagem1', 'nm_link', 'tp_link' ) ) );
        
        ?>

        <h2>Veja Também</h2>            
        <ul>

          <?php
          for($i=0; $i < count($obj); $i++){
            if( strlen($obj[$i]->nm_link) > 0 ){
              $url = $obj[$i]->nm_link;
              if( $obj[$i]->tp_link == 1 ){$target = ' target="_blank"';}
            }else{
              $url = Functions::getUrl($obj[$i]->id_conteudo); 
            }
            ?>
            <li><a href="<?php echo $url; ?>"><?php echo $obj[$i]->nm_h1; ?></a></li>
            <?php 
          }
          $msg = Functions::getFormContatoInterna($getSub);
          ?>

        </ul>
        <h2>Atendimento Pessoal</h2>
        <form action="send.php" method="POST">
          <input type="text" placeholder="Nome:" name="nome" class="form-atend" required>
          <input type="text" placeholder="Telefone:" name="telefone" class="form-atend" required>
          <input type="text" placeholder="E-mail:" name="email" class="form-atend" required>
          <?php echo $msg[0]; ?>
          <input type="submit" value="Solicitar Consulta" class="bt-atend">
        </form> 
        <?php 
      } 
      ?>

    </div>
  </div>

  <!--GALERIA-->


  <div class="container-int row clearfix">
   <?php

   $files = glob("images/galerias/conteudo/". $_GET['codigo'] . "/{*.jpg,*.JPG,*.png,*.gif,*.bmp}", GLOB_BRACE);
   $thumbnail = glob("images/galerias/conteudo/{*.jpg,*.JPG,*.png,*.gif,*.bmp}". $_GET['codigo'] . "/thumbnail/", GLOB_BRACE);


   if($files != ''){

    foreach($files as $img) {
      $thumbnail = (explode('/', $img));
      $thumbnail = "images/galerias/conteudo/". $_GET['codigo'] . "/thumbnail/" . $thumbnail[4];
      ?>
      <div class="col">
        <a href="<?php echo $img; ?>" data-gallery="#blueimp-structure"><img src="<?php echo $img; ?>"></a>
      </div>
      <?php 
    }
  }
  ?>

</div>

<!-- The Bootstrap Image Gallery lightbox, should be a child element of the document body -->
<div id="blueimp-structure" class="blueimp-gallery blueimp-gallery-controls" data-use-bootstrap-modal="false">
 <!-- The container for the modal slides -->
 <div class="slides"></div>
 <!-- Controls for the borderless lightbox -->
 <h3 class="title"></h3>
 <a class="prev"></a>
 <a class="next"></a>
 <a class="close"></a>
 <a class="play-pause"></a>
 <ol class="indicator"></ol>
</div>	    


</section>

<?php include("includes/footer.php");?>

<!-- Galeria -->    
<script src="js/jquery-1.11.3.min.js"></script> 
<script src="js/jquery.blueimp-gallery.min.js"></script>

</body>
</html>

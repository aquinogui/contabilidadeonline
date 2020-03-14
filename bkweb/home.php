<?php include ("includes/inicio.php"); ?>
<?php include ("includes/header.php"); ?>
<?php include ("includes/banner.php"); ?>
<section id="call-action">
    <div class="container">
        <h2>Contabilidade Completa</h2>
        <p>Cumprimos todas as obrigaçoes legais para que sua empresa se matanha totalmente regularizada</p>
        <div class="centraliza">
            <div class="btns">
                <button class="btn-call" style="color:#11a41f;">Simule Sua mensalidade</button>
            </div>
            <div class="btns">
                <button class="btn-call" style="background:none; color:#fff;">Contrate já</button>
            </div>
        </div>
    </section>
    <section id="servicos">
        <div class="container">
           <?php 
           $obj = dao::execute( "conteudo", "Locate", array( FALSE, 1, array(0,6), array( 'id_conteudo', 'nm_conteudo', 'nm_h1', 'tx_resumo', 'nm_imagem1', 'nm_link', 'tp_link' ), 'ASC' ) );


           for($i=0; $i < count($obj); $i++){
              if( strlen($obj[$i]->nm_link) > 0 ){
                $url = $obj[$i]->nm_link;
                if( $obj[$i]->tp_link == 1 ){$target = ' target="_blank"';}else{$target = '';}
            }else{
                $url = Functions::getUrl($obj[$i]->id_conteudo);  
            }


            ?>
            <div class="service">
                <div class="icon"><img src="<?php echo  $obj[$i]->nm_imagem1; ?>" alt=""></div>
                <div class="text">
                    <strong><?php echo $obj[$i]->nm_conteudo; ?></strong>
                    <p><?php echo $obj[$i]->tx_resumo; ?>
                    <a href="<?php echo $url; ?>">Saiba mais</a>
                    </p>
                </div>
            </div>

            <?php } ?>
        </div>
    </div>
</div>
</section>
<section id="empresa">
    <div class="container">
        <h2>Abra ou traga sua empresa</h2>
        <p>Cumprimos todas as obrigaçoes legais para que sua empresa se matanha totalmente regularizada</p>
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

 </div>
</section>

<secion id="facilite">
    <div class="container">
        <h2>Facilite sua vida</h2>
        <p class="linha">A contabilidade da sua empresa de um jeito simples e prático</p>
        
        <img src="images/img-facilite.png"/>
        <div class="text-facilite">
            <h3>Contabilidade online para facilitar a sua vida:</h3>
            <p>Combinamos contadores extremamente competentes e experientes com software de alta tecnologia para você economizar tempo, dinheiro e deixar sua empresa 100% regularizada.</p>
            
            <h3>Nosso serviço é online, seguro e de qualidade</h3>
            <p>Investimos constantemente em alta tecnologia e contamos com profissionais de contabilidade que frequentemente aperfeiçoam suas competências técnicas. Somos motivados pela sua satisfação, somos apaixonados pelo que fazemos e fazemos sempre pensando em você.

                <br>Alta tecnologia, contadores competentes e uma mensalidade que cabe no seu bolso!</p>
                <button>Contrate-já</button>
            </div>
        </div>
    </secion>            
    <!--FIM CONTENT-->
    <?php include ("includes/footer.php"); ?>

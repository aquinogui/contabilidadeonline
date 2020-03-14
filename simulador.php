<?php include ("includes/inicio.php"); ?>
<?php include ("includes/header.php"); ?>
<section id="modelo">
    <div class="banner-in" style="background-image:url(http://contionline.com.br/novo/images/bg2.jpeg)"> </div>
    <div class="container">
        <h1 class="tit-interna">Simule aqui sua mensalidade</h1>
    </div>
    <div class="container">
        <div class="radio-pillbox">
            <radiogroup>
                <div>
                    <input type="radio" name="radio-group" id="js" value="" class="first">
                    <label for="js" class="radio-label">Simples Nacional</label>
                    </input>
                </div>

                <div>
                    <input type="radio" name="radio-group" id="rn" value="e" class="last">
                    <label for="rn">Lucro Presumido</label> </input>
                </div>
            </radiogroup>
        </div>
        <div class="simulador">
            <div class="input-simula">
                <label for="">Quantos Funcionarios na empresa</label>
                <input type="text" value="1"> </div>
            <div class="input-simula">
                <label for="">Quantos Funcionarios na empresa</label>
                <input type="text" value="0"> </div>
            <div class="input-simula">
                <label for="">Quantos Funcionarios na empresa</label>
                <select name="" id="">
                            <option value="">Até R$25.000/mes</option>
                            <option value="">Até R$35.000/mes</option>
                            <option value="">Até R$45.000/mes</option>
                            <option value="">Até R$55.000/mes</option>
                        </select>
            </div>
            <div class="clear"></div>
            <div class="resultado">
                <p>Sua mensaldiade será:</p>
                <p>R$ <span>100</span>/MÊS</p>
                <button class="btn">Contrate Já</button> <small>Não precisamos de nenhuma informação do seu contador atual para o cadastro.</small> </div>
        </div>
    </div>
</section>
<!--FIM CONTENT-->
<?php include ("includes/footer.php"); ?>
<script></script>

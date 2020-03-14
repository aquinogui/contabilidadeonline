<?php 
class PagSeguroSend{

	function __construct(){
		require_once("library/PagSeguroLibrary/PagSeguroLibrary.php");
		require_once("classes/confirmar.class.inc");
		require_once("classes/carrinho.class.inc");

	}

	public function getPedido($idPedido){
		$confirmar = new confirmar;
		$inf_pedido = mysql_fetch_array($confirmar->setPedido($idPedido));
		return $inf_pedido;
	}
	public function getItensPedido($idPedido){
		$obj = dao::execute("item_pedido", "Itens", array($idPedido));
		return $obj;
	}
	public function execultar(){
		$paymentRequest = new PagSeguroPaymentRequest();
		$carrinho = new Carrinho();

		$pedido = $this->getPedido($this->idPedido);
		$itens = $this->getItensPedido($this->idPedido);
		
		$paymentRequest->setCurrency("BRL");
		
		
		foreach ($itens as $key => $value) { 
			
			$result = $carrinho->setPedidoCarrinho($value->id_produto);
			$produtosSql =(mysql_fetch_array($result));
			$paymentRequest->addItem($produtosSql[id_produto], ($produtosSql[nm_produto]) , $value->qt_item , $produtosSql[vl_precoAtual]);    
		}

		$paymentRequest->addItem( 9999, 'SEDEX' , 1, $pedido['vr_frete']);

		if($pedido['vr_impostos'] > 0){
			$paymentRequest->addItem( 9998, 'IMPOSTOS' , 1, $pedido['vr_impostos']);
		}
		$sedexCode = PagSeguroShippingType::getCodeByType('SEDEX');
		$paymentRequest->setShippingType($sedexCode);


		$nome = ($pedido[nm_cliente]);

		$email = ($pedido[nm_email]);
		$endereco = ($pedido[nm_endereco]);
		$complemento = ($pedido[nm_complemento]);
		$bairro = ($pedido[nm_bairro]);
		$cidade = ($pedido[nm_cidade]);
		$estado = ($pedido[nm_estado]);
		if(strlen($pedido['nr_cfp_cnpj']) > 15){
			$tipo_user = "CNPJ";
		}else{
			$tipo_user = "CPF";
		}
		$ddd = ltrim(substr($pedido['nr_telefone'], 0, 2));
		$telefone = str_replace(ltrim(substr($pedido['nr_telefone'], 2)),"-", "");


		$paymentRequest->setSender(

			$nome,
			$email,
			'',
			'',
			/*$ddd,
			$telefone,*/
			$tipo_user,
			$pedido['nr_cfp_cnpj']
			);

		$paymentRequest->setShippingAddress(
			$pedido[nr_cep],
			$endereco,
			$pedido[nr_numero],
			$complemento,
			$bairro,
			$cidade,
			$estado,
			'BRA'
			);

		$paymentRequest->setReference($this->idPedido); 

		$paymentRequest->setRedirectUrl("http://espacoeradeaquario.com.br/produtos/");

		try {  
			$credentials = new PagSeguroAccountCredentials("consultoria@eradeaquario.com.br","EAEEE789569D4478B41003E1ECB08FCF");
			$onlyCheckoutCode = true;  
			$checkoutUrl = $paymentRequest->register($credentials, $onlyCheckoutCode);   
		} catch (PagSeguroServiceException $e) {  
			die($e->getMessage());  
		} 

		if(isset($checkoutUrl)){
			return $checkoutUrl;
		}

	}

}
?>
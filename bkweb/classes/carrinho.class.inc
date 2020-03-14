<?php
session_start();
error_reporting(0);
class Carrinho{
	private $pref = 'media_';

	private function existe($id){
		if(!isset($_SESSION[$this->pref.'produtos'])){
			$_SESSION[$this->pref.'produtos'] = array();
		}

		if(!isset($_SESSION[$this->pref.'produtos'][$id])){
			return false;
		}else{
			return true;
		}
	}

	public function verificaAdiciona($id){
		if(!$this->existe($id)){
			$_SESSION[$this->pref.'produtos'][$id] = 1;
		}else{
			$_SESSION[$this->pref.'produtos'][$id] += 1;
		}
	}

	public function idPresente($id){
		
			$_SESSION[$this->pref.'idPresente'][$id] = $id ;
		
	}

	private function prodExiste($id){
		if(isset($_SESSION[$this->pref.'produtos'][$id])){
			return true;
		}else{
			return false;
		}
	}
	public function deletarProduto($id){
		if(!$this->prodExiste($id)){
			return false;
		}else{
			unset($_SESSION[$this->pref.'produtos'][$id]);
			return true;
		}
	}
	private function isArray($post){
		if(!in_array($post)){
			return true;
		}else{
			return false;
		}
	}
	public function atualizarQuantidade($post){
		
		if($this->isArray($post)){
			foreach($post as $id => $qnt){
				$id = (int)$id;
				$qnt = (int)$qnt;
				
				if($qnt != ''){
					$_SESSION[$this->pref.'produtos'][$id] = $qnt;
				}else{
					unset($_SESSION[$this->pref.'produtos'][$id]);
				}
			}
			return true;
		}else{
			return false;
		}
	}

	public function qntProdutos(){
		if(isset($_SESSION[$this->pref.'produtos'])){
			return count($_SESSION[$this->pref.'produtos']);
		}
	}

	public function precoSession($vl_total){

		if(!isset($_SESSION[$this->pref.'precoTotal'])){
			$_SESSION[$this->pref.'precoTotal'] = $vl_total;
		}else{
			$_SESSION[$this->pref.'precoTotal'] = $vl_total;
		}return true;
		
	}
	public function idPedido($id_pedido){

		if(!isset($_SESSION[$this->pref.'id_pedido'])){
			$_SESSION[$this->pref.'id_pedido'] = $id_pedido;
		}else{
			$_SESSION[$this->pref.'id_pedido'] = $id_pedido;
		}return true;
		
	}
	public function setPedidoCarrinho($id){
		$sql = 'SELECT * FROM tab_produto WHERE id_produto =' . $id . '';
        $result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
    
        return $result;
	}
		public function countQuery($table){
		$sql = 'SELECT * FROM '. $table . '';
        $result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        $count = mysql_fetch_array($result);
        return count($count);
	}
	public function produtoAtivo($id_produto, $statusProd){
		$sql = 'SELECT * FROM tab_produto WHERE id_produto = '. $id_produto . ' AND cd_status = ' . $statusProd . '';
        $result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        $results = mysql_fetch_array($result);
        if($results){
        	return true;
        }else{
        	return false;
        }
	}
}
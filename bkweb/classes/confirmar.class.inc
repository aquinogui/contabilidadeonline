<?php
error_reporting(0);
class Confirmar{
	public function setPedido($id){
		$sql = 'SELECT * FROM tab_pedido WHERE id_pedido =' . $id . '';
        $result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        return $result;
	}
	public function setNome($id){
		$sql = 'SELECT * FROM tab_cliente WHERE id_cliente =' . $id . '';
        $result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        return $result;
	}
	public function setItemProduto($id_pedido){
		$sql = 'SELECT * FROM tab_item_pedido WHERE id_pedido =' . $id_pedido . '';
		 $result = mysql_query($sql);
        //$result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        return $result;
	}
	public static function getReais($x){
		if($x){
			$retorno = str_replace(".",",",$x);	
			return "R$ ".$retorno;	
		} else {
			return "Sem valor";
		}

	}
	public function setItemProdutoNovo($id_produto){
		$sql = 'SELECT * FROM tab_produto WHERE id_produto =' . $id_produto . '';
		 $result = mysql_query($sql);
        //$result = Connector::executeQuery( $sql, Connector::getDefaultLink() );
        return $result;
	}
}	
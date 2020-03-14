<?php 
	
	$url = $_SERVER['REQUEST_URI'];
	$list = explode("_sys", $url);
	
	if(count($list) == 2){
	  $dir = "../../";
	}else{
	  $dir = "";
	}
	
/* VENDA
SELECT p.id_pedido, dt_pedido, c.nm_participante, p.vl_frete, p.cd_status, i.id_produto, pr.id_grupo, pr.id_categoria, sum(i.vl_item*i.nr_quantidade) as vl_item FROM 
tab_pedido p, tab_cadastro c, tab_item i, tab_produtos pr where 
p.id_cliente = c.id_participante and 
p.id_pedido = i.id_pedido and
pr.id_produto = i.id_produto 
group by p.id_pedido
*/

/* FATURAMENTO
SELECT pe.id_pedido, pe.dt_pedido, c.nm_participante, c.nr_telefone, c.nr_cpf, c.nr_rg, c.nm_email, pe.nm_endereco, pe.nr_numero, pe.nm_complemento, pe.nr_cep, pe.nm_bairro,
pe.nm_cidade, pe.cd_estado, p.nm_produto, e.nm_embalagem, i.nr_quantidade, i.vl_item, (i.nr_quantidade * i.vl_item) AS total_item, pe.vl_frete, pe.tp_frete
FROM tab_item i, tab_produtos p, tab_pedido pe, tab_cadastro c, tab_embalagem e
WHERE i.id_produto = p.id_produto
AND pe.id_pedido = i.id_pedido
AND pe.id_cliente = c.id_participante
AND pe.cd_status =  '2'
AND e.id_embalagem = i.id_embalagem
ORDER BY  pe.id_pedido ASC 
*/
	
       require_once($dir . "api/datetime.class.inc");
       require_once($dir . "api/sql.class.inc");
       require_once($dir . "api/connector.class.inc");
	   require_once($dir . "api/entity.class.inc");
       require_once($dir . "api/entitymanager.class.inc");

     class tab_pedido extends Entity {
            // Change this point!
            private $vars = array("id_pedido" => null,
								  "id_cliente" => null,
								  "cd_status" => null,
								  "dt_pedido" => null,
								  "nr_cep" => null,
								  "nm_endereco" => null,
								  "nr_numero" => null,
								  "nm_bairro" => null,
								  "nm_cidade" => null,
								  "cd_estado" => null,
								  "nm_complemento" => null,
								  "nm_referencia" => null,
								  "tx_observacao" => null,
								  "tx_pedidos" => null,
								  "vl_frete" => null,
								  "tp_frete" => null,								  
								  "fl_exportacao" => null,
								  "dt_entrega" => null,
								  "dt_prazo" => null);

            public function __construct() {
            }

            public function __destruct() {
            }

            public function __get($propName) {
                   if (array_key_exists($propName, $this->vars))
                      return $this->vars[$propName];
            }

            public function __set($propName, $value) {
                   if (array_key_exists($propName, $this->vars))
                      $this->vars[$propName] = $value;
            }

            // Change this point!
            public function __toString() {
                   return $this->id_pedido . "-" . $this->id_pedido . "-" . 
						  $this->id_cliente . "-" . $this->id_cliente . "-" . 
						  $this->cd_status . "-" . $this->cd_status . "-" .
						  $this->dt_pedido . "-" . $this->dt_pedido . "-" .
						  $this->nr_cep . "-" . $this->nr_cep . "-" . 
						  $this->nm_endereco . "-" . $this->nm_endereco . "-" .
						  $this->nr_numero . "-" . $this->nr_numero . "-" .
						  $this->nm_cidade . "-" . $this->nm_cidade . "-" . 
						  $this->cd_estado . "-" . $this->cd_estado . "-" . 
						  $this->nm_complemento . "-" . $this->nm_complemento . "-" .
						  $this->nm_referencia . "-" . $this->nm_referencia . "-" .  
						  $this->fl_exportacao . "-" . $this->fl_exportacao . "-" . 
						  $this->tx_observacao . "-" . $this->tx_observacao;
			}

     }

     class tab_pedidos extends EntityManager {
            // Change this point!
            private $tableName = 'tab_pedido'; // Table Name!

			private $keyColumnList = 'id_pedido'; // Key Column List!

			private $anyColumnList = 'id_cliente, cd_status, dt_pedido, nr_cep, nm_endereco, nr_numero, nm_bairro, nm_cidade, cd_estado, nm_complemento, nm_referencia, tx_observacao, tx_pedidos, vl_frete, tp_frete, fl_exportacao, dt_entrega'; // Other Columns!

			private $setColumnList = 'cd_status, nr_cep, nm_endereco, nr_numero, nm_bairro, nm_cidade, cd_estado, nm_complemento, nm_referencia, tx_observacao, fl_exportacao'; // For Update Command!

			private $allColumnList = 'id_pedido, id_cliente, cd_status, dt_pedido, nr_cep, nm_endereco, nr_numero, nm_bairro, nm_cidade, cd_estado, nm_complemento, nm_referencia, tx_observacao, tx_pedidos, vl_frete, tp_frete, fl_exportacao, dt_entrega, dt_prazo'; // For Cursor Command (Select)!
			

            private $vars = array("link" => null, "pageSize" => 12, "pageNumber" => -1, "pageCount" => -1, "numberObjectsTotal" => null);

            private $result = null;

            public function __construct() {
			
            }

            public function __destruct() {
                   $this->close();
            }

            public function __get($propName) {
                   if (array_key_exists($propName, $this->vars))
                      return $this->vars[$propName];
            }

            public function __set($propName, $value) {
                   if (array_key_exists($propName, $this->vars))
                      $this->vars[$propName] = $value;
            }

            public function open($codigo = null, $id_cliente=null, $cd_status = null, $exportado=null, $order = null, $link) {
				
					  if($codigo)
					    $codigo = " and id_pedido='$codigo'";
						
					  if($id_cliente)
					    $id_cliente = " and id_cliente='$id_cliente'";

					  if($cd_status)
					    $cd_status = " and cd_status='$cd_status'";
						
					  if($exportado == 1)
					    $exportado = " and fl_exportacao<'2'";
						
					  if($exportado == 2)
					    $exportado = " and fl_exportacao='2'";
                   
				   	  $statement = "select * from tab_pedido where 1=1 $codigo $id_cliente $cd_status $exportado order by " . $order;

                   $this->result = Connector::executeQuery($statement, $link);
                   $this->calculatePageCount();
				   $this->numberObjectsTotal = $this->setNumberObjects($statement, $link);
                   return $statement;
            }
			
			public function openExportacao($link) {
                   
				   	  $statement = "select * from exportacao_pedido";
					  
					  //SELECT i.id_pedido, i.id_item, i.nr_quantidade, i.vl_item, p.dt_pedido, p.id_cliente, p.nm_endereco, p.nr_numero, p.nm_bairro, p.nm_cidade, p.cd_estado, p.nm_complemento, p.vl_frete, p.cd_status, p.nr_cep, p.fl_exportacao, p.dt_entrega FROM tab_item i, tab_pedido p where p.id_pedido = i.id_pedido

                   $this->result = Connector::executeQuery($statement, $link);
                   $this->calculatePageCount();
				   $this->numberObjectsTotal = $this->setNumberObjects($statement, $link);
                   return $statement;
            }
			
		
			public function changeFlagExportacaoParaPago($link, $id_pag_seg) {
				
				$statement = "update tab_pedido set fl_exportacao='1' where id_pedido='$id_pag_seg'";
								
				$this->result = Connector::executeQuery($statement, $link);
				$this->calculatePageCount();
				$this->numberObjectsTotal = $this->setNumberObjects($statement, $link);
				return $statement;
			}
			
			public function getFormatDateAcrescimo($data){
			  $explode = explode(" ", $data);
			  $nova_data = date('Y-m-d', strtotime("+3 days",strtotime($explode[0])));
			  return $nova_data;
			}
			
			public function updatePagSeg($link, $id_pedido){
				$sql = "Update tab_pedido set fl_exportacao='1', cd_status='2', dt_entrega='" . date("Y-m-d H:i:s") . "', dt_prazo='" . $this->getFormatDateAcrescimo(date("Y-m-d H:i:s")) . "' where id_pedido='" . $id_pedido . "'";
				Connector::executeQuery($sql, $link);
				
				
				
				$id_participante = Connector::getAllName("tab_pedido", "id_cliente", "id_pedido='" . $id_pedido . "'");
				$sql = "Update tab_cadastro set cd_ativo='1' where id_participante='" . $id_participante . "'";
				Connector::executeQuery($sql, $link);
				
			}
			
			
			public function openPedidos($id_cliente = null, $link) {
				
			   	   $statement = "select * from tab_pedido where id_cliente='$id_cliente' order by dt_pedido desc";

                   $this->result = Connector::executeQuery($statement, $link);
                   $this->calculatePageCount();
				   $this->numberObjectsTotal = $this->setNumberObjects($statement, $link);
                   return $statement;
            }
			
			
			public function getNameTable() {
			  return $this->tableName;
            }
			
            public function close() {
                   try {
                   if($this->result != null)
						 @mysql_free_result();
                   } catch(Exception $ex) {
                   } 
                   $this->link = null;
            }

            private function calculatePageCount() {
                    $this->pageCount = mysql_affected_rows() / $this->pageSize;
                    if(mysql_affected_rows() % $this->pageSize > 0)
                       $this->pageCount = ceil($this->pageCount);
                    $this->pageNumber = 1;
            }

            // Change this point!
            private function getObject($row) {
                    $obj = new tab_pedido();
					$obj->id_pedido = $row->id_pedido;
					$obj->id_cliente = $row->id_cliente;
					$obj->cd_status = $row->cd_status;
					$obj->dt_pedido = $row->dt_pedido;
					$obj->nr_cep = $row->nr_cep;
					$obj->nm_endereco = $row->nm_endereco;
					$obj->nm_bairro = $row->nm_bairro;
					$obj->nr_numero = $row->nr_numero;
					$obj->nm_cidade = $row->nm_cidade;
					$obj->cd_estado = $row->cd_estado;
					$obj->nm_complemento = $row->nm_complemento;
					$obj->nm_referencia = $row->nm_referencia;
					$obj->tx_observacao = $row->tx_observacao;
					$obj->tx_pedidos = $row->tx_pedidos;
					$obj->vl_frete = $row->vl_frete;
					$obj->tp_frete = $row->tp_frete;
					$obj->fl_exportacao = $row->fl_exportacao;
					$obj->dt_entrega = $row->dt_entrega;
					return $obj;
            }
            
            private function refreshData() {
                    $pageNumber = $this->pageNumber;
                    $this->open("", "", "", "", "id_pedido", $this->link);
                    $this->pageNumber = $pageNumber;
            }
            
            private function getData() {
                   $array = array();
                   $i = 0;
                   while (($row = mysql_fetch_object($this->result)) && ($i < $this->pageSize)) {
                         $array[$i] = $this->getObject($row);
                         $i++;
                   }
                   return $array;
            }

            public function firstPage() {
                   $this->pageNumber = 1;
                   return $this->gotoPage($this->pageNumber);
            }

            public function previousPage() {
                   if($this->pageNumber > 1)
                      $this->pageNumber = $this->pageNumber - 1;
                   return $this->gotoPage($this->pageNumber);
            }

            public function nextPage() {
                   if($this->pageNumber < $this->pageCount)
                      $this->pageNumber = $this->pageNumber + 1;
                   return $this->gotoPage($this->pageNumber);
            }

            public function lastPage() {
                   $this->pageNumber = $this->pageCount;
                   return $this->gotoPage($this->pageNumber);
            }


            public function gotoPage($pageNumber) {
                   if($pageNumber < 1) $pageNumber = 1;
                   if($pageNumber > $this->pageCount) $pageNumber = $this->pageCount;
                   $recordNumber = 0;
                   if($this->pageCount > 0) {
                     $recordNumber = ($pageNumber - 1) * $this->pageSize;
                     mysql_data_seek($this->result, $recordNumber);
                   }
                   return $this->getData();
            }
			

            public function refreshPage() {
                   return $this->gotoPage($this->pageNumber);
            }

            // Change this point!
            public function insert(tab_pedido $obj) {
                   $statement = SQL::getInsertStatement($this->tableName, $this->anyColumnList);
				   $statement = SQL::setString($statement, 'id_cliente', $obj->id_cliente);
				   $statement = SQL::setString($statement, 'cd_status', $obj->cd_status);
				   $statement = SQL::setString($statement, 'dt_pedido', $obj->dt_pedido);
				   $statement = SQL::setString($statement, 'nr_cep', $obj->nr_cep);
				   $statement = SQL::setString($statement, 'nm_endereco', $obj->nm_endereco);
				   $statement = SQL::setString($statement, 'nr_numero', $obj->nr_numero);
				   $statement = SQL::setString($statement, 'nm_bairro', $obj->nm_bairro);
				   $statement = SQL::setString($statement, 'nm_cidade', $obj->nm_cidade);
				   $statement = SQL::setString($statement, 'cd_estado', $obj->cd_estado);
				   $statement = SQL::setString($statement, 'dt_pedido', $obj->dt_pedido);
				   $statement = SQL::setString($statement, 'nm_complemento', $obj->nm_complemento);
				   $statement = SQL::setString($statement, 'nm_referencia', $obj->nm_referencia);
				   $statement = SQL::setString($statement, 'tx_observacao', $obj->tx_observacao);
				   $statement = SQL::setString($statement, 'tx_pedidos', $obj->tx_pedidos);
				   $statement = SQL::setString($statement, 'dt_entrega', $obj->dt_entrega);
				   $statement = SQL::setString($statement, 'vl_frete', $obj->vl_frete);
				   $statement = SQL::setString($statement, 'fl_exportacao', $obj->fl_exportacao);
				   $statement = SQL::setString($statement, 'tp_frete', $obj->tp_frete);

				   Connector::executeQuery($statement, $this->link);
                   $this->refreshData();
                   return $statement;
            }

            // Change this point!
            public function update(tab_pedido $obj) {
                   $statement = SQL::getUpdateStatement($this->tableName, $this->setColumnList, $this->keyColumnList);
				   $statement = SQL::setString($statement, 'id_pedido', $obj->id_pedido);
				   $statement = SQL::setString($statement, 'cd_status', $obj->cd_status);
				   $statement = SQL::setString($statement, 'nr_cep', $obj->nr_cep);
				   $statement = SQL::setString($statement, 'nm_endereco', $obj->nm_endereco);
				   $statement = SQL::setString($statement, 'nr_numero', $obj->nr_numero);
				   $statement = SQL::setString($statement, 'nm_bairro', $obj->nm_bairro);
				   $statement = SQL::setString($statement, 'nm_cidade', $obj->nm_cidade);
				   $statement = SQL::setString($statement, 'cd_estado', $obj->cd_estado);
				   $statement = SQL::setString($statement, 'dt_pedido', $obj->dt_pedido);
				   $statement = SQL::setString($statement, 'nm_complemento', $obj->nm_complemento);
				   $statement = SQL::setString($statement, 'nm_referencia', $obj->nm_referencia);
				   $statement = SQL::setString($statement, 'tx_observacao', $obj->tx_observacao);
				   $statement = SQL::setString($statement, 'fl_exportacao', $obj->fl_exportacao);
				   
				   Connector::executeQuery($statement, $this->link);
                   $this->refreshData();
                   return $statement;
            }

            // Change this point!
            public function delete($id_pedido) {
                   $statement = SQL::getDeleteStatement($this->tableName, $this->keyColumnList);
                   $statement = SQL::setString($statement, 'id_pedido', $id_pedido);
                   Connector::executeQuery($statement, $this->link);
                   $this->refreshData();
                   return $statement;
            }
			
			public function alteraStatus($id_pedido) {
                   
				   $statement = "update tab_pedido set cd_status = 3 where id_pedido = $id_pedido";
				   
                   Connector::executeQuery($statement, $this->link);
                   $this->refreshData();
                   return $statement;

            }
				   
            // Change this point!
            public function locate($id_pedido) {
                   $statement = SQL::getLocateStatement($this->tableName, $this->allColumnList, $this->keyColumnList);
                   $statement = SQL::setInteger($statement, 'id_pedido', $id_pedido);
                   $query = Connector::executeQuery($statement, $this->link);
                   if($row = mysql_fetch_object($query)) {
                         return $this->getObject($row);
                   }
                   return null;
            }
			
			
			public function getValorTotal($link, $id_pedido) {
                   $statement = "Select SUM(vl_item*nr_quantidade) as total from tab_item where id_pedido='$id_pedido'";

                   $query = Connector::executeQuery($statement, $link);
                   if($row = mysql_fetch_object($query)) {
                         return $row->total;
                   }
                   return 0;
            }
			
			
			public function darBaixa($link, $id_pedido) {
                   $statement = "UPDATE tab_pedido set cd_status='5' where id_pedido='$id_pedido'";
                   $query = Connector::executeQuery($statement, $link);

            }
			
			
			public function getLastId($link) {
                   $statement = "Select id_pedido from tab_pedido order by id_pedido desc";
                   $query = Connector::executeQuery($statement, $link);
                   if($row = mysql_fetch_object($query)) {
                         return $row->id_pedido;
                   }
                   return 1;
            }

			public function selectAll() {
			       $array = array();
                   if($this->pageCount > 0) {
                     mysql_data_seek($this->result, 0);
   				     $i = 0;
                     while ($row = mysql_fetch_object($this->result)) {
                         $array[$i] = $this->getObject($row);
                         $i++;
                     }
				   }
                   return $array;
            }
			

			public function setNumberObjects($statement, $link){
				return @mysql_num_rows(Connector::executeQuery($statement, $link));
			}								

            // Change this point!
            public function __toString() {
                   return "tab_pedidos Class";
            }
     }
	 
?>
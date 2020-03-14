<?php 

	

	$url = $_SERVER['REQUEST_URI'];

	$list = explode("_sys", $url);

	

	if(count($list) == 2){

	  $dir = "../../";

	}else{

	  $dir = "";

	}

	

       require_once($dir . "api/datetime.class.inc");

       require_once($dir . "api/sql.class.inc");

       require_once($dir . "api/connector.class.inc");

	   require_once($dir . "api/entity.class.inc");

       require_once($dir . "api/entitymanager.class.inc");



     class tab_item extends Entity {

            // Change this point!

            private $vars = array("id_pedido" => null,

								  "id_item" => null,

								  "id_produto" => null,

								  "nr_quantidade" => null,

								  "id_embalagem" => null,

								  "vl_item" => null);

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

						  $this->id_item . "-" . $this->id_item . "-" . 

						  $this->id_produto . "-" . $this->id_produto . "-" . 

						  $this->nr_quantidade . "-" . $this->nr_quantidade . "-" . 

						  $this->vl_item . "-" . $this->vl_item;

			}



     }



     class tab_items extends EntityManager {

            // Change this point!

            private $tableName = 'tab_item'; // Table Name!



			private $keyColumnList = 'id_pedido'; // Key Column List!



			private $anyColumnList = 'id_pedido, id_produto, nr_quantidade, id_embalagem, vl_item'; // Other Columns!



			private $setColumnList = 'id_item, id_produto, nr_quantidade, id_embalagem, vl_item'; // For Update Command!



			private $allColumnList = 'id_pedido, id_item, id_produto, nr_quantidade, id_embalagem, vl_item'; // For Cursor Command (Select)!

			



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



            public function open($link, $order, $id_pedido) {

				

				$statement = "select * from tab_item where id_pedido=" . $id_pedido;

				

				$this->result = Connector::executeQuery($statement, $link);

				$this->calculatePageCount();

				$this->numberObjectsTotal = $this->setNumberObjects($statement, $link);

				return $statement;

            }

			

			public function openItens($link, $id_pedido) {

				

				$statement = "select * from tab_item where id_pedido=" . $id_pedido;

				$this->result = Connector::executeQuery($statement, $link);

				$this->calculatePageCount();

				$this->numberObjectsTotal = $this->setNumberObjects($statement, $link);

				return $statement;

            }

			

			public function getValorPag($link, $cod){

				

				$statement = "SELECT (sum(vl_item*nr_quantidade)+(Select vl_frete from tab_pedido where id_pedido='$cod')) as total FROM tab_item WHERE id_pedido='$cod'";



				$query = Connector::executeQuery($statement, $this->link);

				

				$row = mysql_fetch_object($query);



				return $row->total;

			}

			

			public function getNameTable() {

			  return $this->tableName;

            }

			

            public function close() {

                   try {

                   if($this->result != null)

						 mysql_free_result($this->result);

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

                    $obj = new tab_item();

					$obj->id_pedido = $row->id_pedido;

					$obj->id_item = $row->id_item;

					$obj->id_produto = $row->id_produto;

					$obj->nr_quantidade = $row->nr_quantidade;

					$obj->id_embalagem = $row->id_embalagem;

					$obj->vl_item = $row->vl_item;

					return $obj;

            }

            

            private function refreshData() {

                    $pageNumber = $this->pageNumber;

                    $this->open($this->link, "", 1);

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

            public function insert(tab_item $obj) {

                   $statement = SQL::getInsertStatement($this->tableName, $this->anyColumnList);

				   $statement = SQL::setString($statement, 'id_pedido', $obj->id_pedido);

				   $statement = SQL::setString($statement, 'id_produto', $obj->id_produto);

				   $statement = SQL::setString($statement, 'nr_quantidade', $obj->nr_quantidade);

				   $statement = SQL::setString($statement, 'id_embalagem', $obj->id_embalagem);

				   $statement = SQL::setString($statement, 'vl_item', $obj->vl_item);

				   

				   Connector::executeQuery($statement, $this->link);

                   $this->refreshData();

                   return $statement;

            }



            // Change this point!

            public function update(tab_item $obj) {

                   $statement = SQL::getUpdateStatement($this->tableName, $this->setColumnList, $this->keyColumnList);

				   $statement = SQL::setString($statement, 'id_pedido', $obj->id_pedido);

				   $statement = SQL::setString($statement, 'id_item', $obj->id_item);

				   $statement = SQL::setString($statement, 'id_produto', $obj->id_produto);

				   $statement = SQL::setString($statement, 'nr_quantidade', $obj->nr_quantidade);

				   $statement = SQL::setString($statement, 'id_embalagem', $obj->id_embalagem);

				   $statement = SQL::setString($statement, 'vl_item', $obj->vl_item);



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

				return mysql_num_rows(Connector::executeQuery($statement, $link));

			}								



            // Change this point!

            public function __toString() {

                   return "tab_items Class";

            }

     }

	 

?>
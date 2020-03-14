<?php
     class SQL {

            private function __construct() {
            }

            private static function getParameterList($columnList) {
                    $columns = explode(",", $columnList);
                    $result = '';
                    for ($i = 0; $i < count($columns); $i++) {
                        $columnName = trim($columns[$i]);
                        if($i > 0) $result = $result . ', ';
                        $result = $result . '%' . $columnName . '%';
                    }
                    return $result;
            }

            private static function getSetParameterList($setColumnList) {
                    $columns = explode(",", $setColumnList);
                    $result = '';
                    for ($i = 0; $i < count($columns); $i++) {
                        $columnName = trim($columns[$i]);
                        if($i > 0) $result = $result . ', ';
                        $result = $result . $columnName . '=%' . $columnName . '%';
                    }
                    return $result;
            }

            private static function getConditionalStatement($keyColumnList) {
                    $columns = explode(",", $keyColumnList);
                    $result = '';
                    for ($i = 0; $i < count($columns); $i++) {
                        $columnName = trim($columns[$i]);
                        if($i > 0) $result = $result . ' AND ';
                        $result = $result . $columnName . '=%' . $columnName . '%';
                    }
                    return $result;
            }
			
			private static function getConditionalStatementOr($keyColumnList) {
                    $columns = explode(",", $keyColumnList);
                    $result = '';
                    for ($i = 0; $i < count($columns); $i++) {
                        $columnName = trim($columns[$i]);
                        if($i > 0) $result = $result . ' OR ';
                        $result = $result . $columnName . " LIKE '%" . $columnName . "%'";
                    }
                    return $result;
            }			

            public static function getInsertStatement($tableName, $columnList) {
                   return 'INSERT INTO ' . $tableName . ' (' . $columnList. ') ' .
                          'VALUES(' . self::getParameterList($columnList) . ')';
            }

            public static function getUpdateStatement($tableName, $setColumnList, $keyColumnList) {
                   return 'UPDATE ' . $tableName . ' SET ' .
                          self::getSetParameterList($setColumnList) . ' WHERE ' .
                          self::getConditionalStatement($keyColumnList);
            }
			

            public static function getDeleteStatement($tableName, $keyColumnList) {
                   return 'DELETE FROM ' . $tableName . ' WHERE ' .
                          self::getConditionalStatement($keyColumnList);
            }

            public static function getLocateStatement($tableName, $allColumnList, $keyColumnList) {
                   return 'SELECT ' . $allColumnList . ' FROM ' . $tableName . ' WHERE ' .
                          self::getConditionalStatement($keyColumnList);
            }
			
            public static function getLocateStatementOr($tableName, $allColumnList, $keyColumnList) {
                   return 'SELECT ' . $allColumnList . ' FROM ' . $tableName . ' WHERE ' .
                          self::getConditionalStatementOr($keyColumnList);
            }			

            public static function getCursorStatement($tableName, $allColumnList) {
                   return 'SELECT ' . $allColumnList . ' FROM ' . $tableName;
            }

            public static function getNextIdStatement($tableName, $keyColumn) {
                   return 'SELECT MAX(' . $keyColumn . ')+1 FROM ' . $tableName;
            }
            
            public static function setInteger($statement, $columnName, $columnValue) {
                   if(!is_integer($columnValue))
                     $columnValue = 0;
                   return str_ireplace('%' . $columnName . '%', $columnValue, $statement);
            }

            public static function setDouble($statement, $columnName, $columnValue) {
                   if(!is_double($columnValue))
                     $columnValue = 0.0;
                   return str_ireplace('%' . $columnName . '%', $columnValue, $statement);
            }

            public static function setString($statement, $columnName, $columnValue) {
					$columnValue = Functions::rteSafe($columnValue);
                   return str_ireplace('%' . $columnName . '%', '"' . $columnValue . '"', $statement);
            }

            public static function setNull($statement, $columnName) {
                   return str_ireplace('%' . $columnName . '%', 'NULL', $statement);
            }
     }
?>
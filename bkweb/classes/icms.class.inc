<?php 
class Icms{
  function __construct()
  {
    define("TAX_TABLE_QUERY", "select * from tab_taxa_estado where cd_uf = '[1]'");
    define("ICMS", 0);
    define("MVA", 1);
    define("ICMS_ST", 2);
  }
//----------------------------------------------------------------------------
  public function get_link() {
  /*$hostname = 'vernizskanialv.mysql.dbaas.com.br';
  $username = 'vernizskanialv';
  $password = 'skaniadms86';
  $database = 'vernizskanialv';*/
  $hostname = 'vernizskanialv.mysql.dbaas.com.br';
  $username = 'vernizskanialv';
  $password = 'skaniadms86';
  $database = 'vernizskanialv';

  $link = mysqli_connect($hostname, $username, $password)
  or die('Cannot to connect to Database: ' . mysqli_error());
  mysqli_select_db($link, $database)
  or die('Cannot to select Database: ' . $database);
  mysqli_set_charset( $link, "UTF-8" );

  return $link;
}
//----------------------------------------------------------------------------
public function get_taxes($cd_uf) {

  $taxes = array(0.0, 0.0, 0.0);
  $link = $this->get_link();

  if($link) {
    $query = str_replace("[1]", $cd_uf, TAX_TABLE_QUERY);
    $result = mysqli_query($link, $query);
    if($result) {
      if ($row = mysqli_fetch_assoc($result)) {
        $taxes = array(
          $row["nr_aliq_icms"] * 1.0,
          $row["nr_mva"] * 1.0,
          $row["nr_aliq_icms_st"] * 1.0
          );
        mysqli_free_result($result);
      }
    }
    mysqli_close($link);
  }
  return $taxes;
}
//----------------------------------------------------------------------------
public function calculate_icms($vr_unit, $vr_frete, $cd_uf) {
  throw new Exception("Funcão calculate_icms(...) está 'deprecated'. Usar calculate_icms2(value, taxes).");
}
//----------------------------------------------------------------------------
public function calculate_icms2($value, $taxes) {
  
  // Get taxes from table...
  $tx_icms = $taxes[ICMS];
  $tx_mva = $taxes[MVA];
  $tx_icms_st = $taxes[ICMS_ST];

  // Calculate Value of ICMS...
  $vr_icms = $value * ($tx_icms/100.0) * 1.0;
  $vr_base_st = round($value * (1+($tx_mva/100.0)) * 1.0, 2);
  $vr_icms_st = round($vr_base_st * ($tx_icms_st/100.0) * 1.0, 2);
  $vr_icms_st_final = round($vr_icms_st - $vr_icms, 2);
  $total = $value + $vr_icms_st_final;

  $response = array(
    "BASE_ICMS" => round($value, 2),
    "ALIQ_ICMS" => round($tx_icms, 4),
    "VALOR_ICMS" => round($vr_icms, 2),
    "BASE_ICMS_ST" => round($vr_base_st, 2),
    "ALIQ_ICMS_ST" => round($tx_icms_st, 4),
    "VALOR_ICMS_ST" => round($vr_icms_st_final, 2),
    "MVA" => round($tx_mva, 4),
    "TOTAL" => round($total, 2)
    );
  
  return $response;
}
//----------------------------------------------------------------------------
public function pt_decimal_format($number) {
  return number_format($number, 2, ',', '.');
}
//----------------------------------------------------------------------------]
}
?>
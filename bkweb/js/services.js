//------------------------------------------------------------------------
function GetXmlHttpObject() {
  var xmlHttp = null;
  try {
    // Firefox, Opera 8.0+, Safari
    xmlHttp=new XMLHttpRequest();
  } catch (e) {
    // Internet Explorer
    try {
      xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
    } catch (e) {
      xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
  }
  return xmlHttp;
}


function getRefToDiv(divID) {   
    if( document.layers ) { //Netscape layers   
        return document.layers[divID]; }   
    if( document.getElementById ) { //DOM; IE5, NS6, Mozilla, Opera   
        return document.getElementById(divID); }   
    if( document.all ) { //Proprietary DOM; IE4   
        return document.all[divID]; }   
    if( document[divID] ) { //Netscape alternative   
        return document[divID]; }   
    return false;   
}
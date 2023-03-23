<?php
class temperatura{
 public $link='';
 function __construct($valor_temperatura){
  $this->connect();
  $this->storeInDB($valor_temperatura);
 }
    
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'sp') or die('Cannot select the DB');
 }
 
 function storeInDB($valor_temperatura){
  $query = "insert into temperatura set valor_temperatura='".$valor_temperatura."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['valor_temperatura'] != ''){
 $temperatura=new temperatura($_GET['valor_temperatura']);
}


?>
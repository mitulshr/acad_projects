<!DOCTYPE html>

<html>     
   <head>
       <title>eBay Search</title>    
       <link rel="stylesheet" type="text/css" href="hw6style.css">

    <script>
      
       
       function validate()
        {
          var flag = 1;
          var alertmsg= "";
          if(document.getElementById("keyword").value == "")
            { 
              alertmsg += "Please Enter Value for Keyword\n";
              flag =0; 
            }
          if(document.getElementById("min").value != "")
            {
              if(!(/^\d*(\.\d+)?$/).test(document.getElementById("min").value))
               { 
                 alertmsg += "Please Enter a positive numeric amount for Minumum price value\n";
                 flag =0;
               }     
            }
          if(document.getElementById("max").value != "")
            {
              if(!(/^\d*(\.\d+)?$/).test(document.getElementById("max").value))
               {
                alertmsg += "Please Enter a positive numeric amount for Maximum price value\n";
                flag =0;
               }  
            }    
          if((document.getElementById("min").value != "") && (document.getElementById("min").value != ""))
             {
              var mini =  parseInt(document.getElementById("min").value);
              var maxi =  parseInt(document.getElementById("max").value);
              if(mini > maxi)
              {
                alertmsg += "Minimum amount cannot be more than maximum amount\n";
                flag =0;
              }
             } 
          if(document.getElementById("shipdays").value != "")
          {
          if((/^\d*$/).test(document.getElementById("shipdays").value))
            {
             if(parseInt(document.getElementById("shipdays").value) < 1)
              {
              alertmsg += "Minimum handling time cannot be less than 1\n";
              flag = 0;
              }
            }  
          else
              {
              alertmsg += "Minimum handling can take only Integer values\n";
              flag = 0;
              }
            
         }
         if(flag == 0)
           {
             alert(alertmsg);
             return false; 
           }
         return true;    
        }
       
       function resetValues()
        {
          document.getElementById("min").value = "";
          document.getElementById("max").value = "";  
          document.getElementById("keyword").value = "";
          document.getElementById("con1").checked = false;
          document.getElementById("con2").checked = false;
          document.getElementById("con3").checked = false;
          document.getElementById("con4").checked = false;
          document.getElementById("con5").checked = false;
          document.getElementById("buy1").checked = false;
          document.getElementById("buy2").checked = false;
          document.getElementById("buy3").checked = false;
          document.getElementById("shty1").checked = false;
          document.getElementById("shty2").checked = false;
          document.getElementById("rtracc").checked = false;
          document.getElementById("shipdays").value = "";  
          document.getElementById("rpp").selectedIndex = 0; 
          document.getElementById("bstmatch").selectedIndex = 0; 
          document.getElementById("results").innerHTML = "";        
        }
       </script>
    </head>
   
    <body>
    <div id="header">
        <table>
          <tr>
            <td>
              <img src="ebay.jpg" height="100" width="130">     
            </td>
            <td>
              Shopping
            </td>
          </tr>
        </table>
    </div>    
    <div id="formtable">
        <br>
        <form id="myForm" action="hw6.php" method="post">
        <table>
    
        <tr class="forhr">
            <td class= "tdhr">         
                <b> Key Words*:</b>
            </td>
            <td class= "tdhr">
             <input type="text" size="50" name="keyword" id ="keyword" value = "<?php
echo isset($_POST['keyword']) ? $_POST['keyword'] : NULL;
?>"/>
            </td>
            </tr>
            <tr class="forhr">    
            <td class= "tdhr">
               <b>Price Range:</b>
            </td>
            <td class= "tdhr">
                from $ 
                <input type="text" size="5"  name="rangemin" id ="min" value = "<?php
echo isset($_POST['rangemin']) ? $_POST['rangemin'] : NULL;
?>"> 
                to $
                <input type="text" size="5" name="rangemax" id = "max" value = "<?php
echo isset($_POST['rangemax']) ? $_POST['rangemax'] : NULL;
?>"> 
                </td>        
            </tr>
            <tr>
            
           
                
            <td class= "tdhr">
                <b>Condition:</b>
                </td>
            <td class= "tdhr">
                <input id = "con1" type="checkbox" name="cond[]" <?php
if (isset($_POST['cond'])) {
    $con = $_POST['cond'];
    for ($i = 0; $i < count($con); $i++) {
        if ($con[$i] == "new") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?> value="new">New
                <input id = "con2" type="checkbox" name="cond[]"  value="used" <?php
if (isset($_POST['cond'])) {
    $con = $_POST['cond'];
    for ($i = 0; $i < count($con); $i++) {
        if ($con[$i] == "used") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Used
                <input id = "con3" type="checkbox" name="cond[]"  value="verygood" <?php
if (isset($_POST['cond'])) {
    $con = $_POST['cond'];
    for ($i = 0; $i < count($con); $i++) {
        if ($con[$i] == "verygood") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Very Good
                <input id = "con4" type="checkbox" name="cond[]"  value="good" <?php
if (isset($_POST['cond'])) {
    $con = $_POST['cond'];
    for ($i = 0; $i < count($con); $i++) {
        if ($con[$i] == "good") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Good
                <input id = "con5" type="checkbox" name="cond[]"  value="acceptable" <?php
if (isset($_POST['cond'])) {
    $con = $_POST['cond'];
    for ($i = 0; $i < count($con); $i++) {
        if ($con[$i] == "acceptable") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Acceptable
                </td>
            </tr>
            <tr>
            <td class= "tdhr">
                <b>Buying Format:</b>
                </td>
            <td class= "tdhr">
                <input id ="buy1" type="checkbox" name="buyformat[]"  value="now" <?php
if (isset($_POST['buyformat'])) {
    $arr = $_POST['buyformat'];
    for ($i = 0; $i < count($arr); $i++) {
        if ($arr[$i] == "now") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Buy It Now
                <input id ="buy2" type="checkbox" name="buyformat[]"  value="auction" <?php
if (isset($_POST['buyformat'])) {
    $arr = $_POST['buyformat'];
    for ($i = 0; $i < count($arr); $i++) {
        if ($arr[$i] == "auction") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Auction
                <input id ="buy3" type="checkbox" name="buyformat[]"  value="ads"<?php
if (isset($_POST['buyformat'])) {
    $arr = $_POST['buyformat'];
    for ($i = 0; $i < count($arr); $i++) {
        if ($arr[$i] == "ads") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Classified Ads
                </td>
            </tr>
            <tr>
              <td class= "tdhr">
                <b>Seller:</b>
                </td>
              <td class= "tdhr">
                <input id ="rtracc" type="checkbox" name="seller" value="retaccept"  <?php
echo empty($_POST['seller']) ? '' : ' checked="checked" ';
?>">Return Accepted
                </td>
            </tr>
            
            <tr>
            <td class= "tdhr">
                <b>Shipping:</b>
                </td>   
            <td class= "tdhr">
                <input id = "shty1" type="checkbox" name="shipping[]" value="freeship" <?php
if (isset($_POST['shipping'])) {
    $arr = $_POST['shipping'];
    for ($i = 0; $i < count($arr); $i++) {
        if ($arr[$i] == "freeship") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Free Shipping<br>
                <input id = "shty2" type="checkbox" name="shipping[]" value="expiteship" <?php
if (isset($_POST['shipping'])) {
    $arr = $_POST['shipping'];
    for ($i = 0; $i < count($arr); $i++) {
        if ($arr[$i] == "expiteship") {
            echo "checked=\"checked\"";
            break;
        }
    }
}
?>>Expidite Shipping Available<br>
                Max handing time(days):  <input type="text" size="5" id = "shipdays" name="shipdays" value = "<?php
echo isset($_POST['shipdays']) ? $_POST['shipdays'] : NULL;
?>" >
                </td>  
            </tr>
            
        <tr>
            <td class= "tdhr">
              <b>Sort by:</b>
            </td>
            <td class= "tdhr">
            <select id= "bstmatch"  name="sort">
                <option value="BestMatch" <?php
if (isset($_POST['sort']) && $_POST['sort'] == 'BestMatch')
    echo ' selected="selected"';
?> selected>Best Match</option>
                <option value="CurrentPriceHighest" <?php
if (isset($_POST['sort']) && $_POST['sort'] == 'CurrentPriceHighest')
    echo ' selected="selected"';
?>>Price: highest first</option>
                <option value="PricePlusShippingHighest" <?php
if (isset($_POST['sort']) && $_POST['sort'] == 'PricePlusShippingHighest')
    echo ' selected="selected"';
?> >Price + Shipping: highest first</option>
                <option value="PricePlusShippingLowest" <?php
if (isset($_POST['sort']) && $_POST['sort'] == 'PricePlusShippingLowest')
    echo ' selected="selected"';
?> >Price + Shipping: lowest first</option>
                </select>
            </td>
            </tr>
        <tr>
            <td class= "tdhr">
            <b>Result Per page:</b>
            </td>
            <td class= "tdhr">
            <select name="resperpg" id ="rpp">
                <option value="5" <?php
if (isset($_POST['resperpg']) && $_POST['resperpg'] == '5')
    echo ' selected="selected"';
?> selected >5</option>
                <option value="10"<?php
if (isset($_POST['resperpg']) && $_POST['resperpg'] == '10')
    echo ' selected="selected"';
?> > 10</option>
                <option value="15" <?php
if (isset($_POST['resperpg']) && $_POST['resperpg'] == '15')
    echo ' selected="selected"';
?>>15</option>
                <option value="20"<?php
if (isset($_POST['resperpg']) && $_POST['resperpg'] == '20')
    echo ' selected="selected"';
?>>20</option>    
                </select>
            </td>
            </tr>
            <tr>
              <td>
                </td>
            <td align="right">
                <div id="buttons" aling = "right">
                <input type="button" value="clear" name="clear" onclick ="resetValues()">
                <input type="submit" value="search" name="search" onclick="return validate()">
                </div>
                </td>
            </tr>
        </table> 
        </form>
        <br>
        </div>   

<?php

$apiCall = '';
if (isset($_POST['search'])) {
    $index            = 0;
    $endpoint         = 'http://svcs.ebay.com/services/search/FindingService/v1'; // URL to call
    $responseEncoding = 'XML';
    $appID            = 'USC0098a7-f39a-485d-9653-1f8fb04952a';
    $safeKeyword      = urlencode(utf8_encode($_POST['keyword']));
    $apiCall          = "$endpoint?OPERATION-NAME=findItemsAdvanced" . "&siteid=0" . "&SERVICE-VERSION=1.0.0" . "&SECURITY-APPNAME=$appID" . "&keywords=$safeKeyword";
    if (!empty($_POST['rangemin'])) {
        $min     = $_POST['rangemin'];
        $apiCall = $apiCall . "&itemFilter($index).name=MinPrice";
        $apiCall = $apiCall . "&itemFilter($index).value=$min";
        $index++;
    }
    if (!empty($_POST['rangemax'])) {
        $max     = $_POST['rangemax'];
        $apiCall = $apiCall . "&itemFilter($index).name=MaxPrice";
        $apiCall = $apiCall . "&itemFilter($index).value=$max";
        $index++;
    }
    
    if (isset($_POST['cond'])) {
        $condition = $_POST['cond'];
        $apiCall   = $apiCall . "&itemFilter($index).name=Condition";
        $condIndex = 0;
        for ($i = 0; $i < count($condition); $i++) {
            if ($condition[$i] == "new") {
                $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=1000";
                $condIndex++;
            }
            
            if ($condition[$i] == "used") {
                $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=3000";
                $condIndex++;
            }
            
            if ($condition[$i] == "v     erygood") {
                $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=4000";
                $condIndex++;
            }
            
            if ($condition[$i] == "good") {
                $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=5000";
                $condIndex++;
            }
            
            
            if ($condition[$i] == "acceptable") {
                $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=6000";
                $condIndex++;
            }
        }
        $index++;
    }
    
    
    if (isset($_POST['buyformat'])) {
        $buyformat = $_POST['buyformat'];
        $buyIndex  = 0;
        $apiCall   = $apiCall . "&itemFilter($index).name=ListingType";
        for ($j = 0; $j < count($buyformat); $j++) {
            if ($buyformat[$j] == "now") {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=FixedPrice";
                $buyIndex++;
            }
            
            if ($buyformat[$j] == "auction") {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=Auction";
                $buyIndex++;
            }
            
            if ($buyformat[$j] == "ads") {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=Classified";
                $buyIndex++;
            }
            
        }
        $index++;
    }
    
    if (isset($_POST['seller'])) {
        $apiCall = $apiCall . "&itemFilter($index).name=ReturnsAcceptedOnly";
        $apiCall = $apiCall . "&itemFilter($index).value=true";
        $index++;
    }
    
    
    if (isset($_POST['shipping'])) {
        $shipping = $_POST['shipping'];
        for ($k = 0; $k < count($shipping); $k++) {
            if ($shipping[$k] == "freeship") {
                $apiCall = $apiCall . "&itemFilter($index).name=FreeShippingOnly";
                $apiCall = $apiCall . "&itemFilter($index).value=true";
                $index++;
            }
            if ($shipping[$k] == "expiteship") {
                $apiCall = $apiCall . "&itemFilter($index).name=ExpeditedShippingType";
                $apiCall = $apiCall . "&itemFilter($index).value=Expedited";
                $index++;
            }
        }
    }
    
    if (!empty($_POST['shipdays'])) {
        $shipdays = $_POST['shipdays'];
        $apiCall  = $apiCall . "&itemFilter($index).name=MaxHandlingTime";
        $apiCall  = $apiCall . "&itemFilter($index).value=$shipdays";
        $index++;
    }
    
    $sort    = $_POST['sort'];
    $apiCall = $apiCall . "&sortOrder";
    $apiCall = $apiCall . "=$sort";
    
    $itemsPerPage = intval($_POST['resperpg']);
    //$apiCall = $apiCall . "&itemFilter($index).name=paginationInput.entriesPerPage";
    $apiCall      = $apiCall . "&paginationInput.entriesPerPage=$itemsPerPage";
    //$index++;     
    $apiCall      = $apiCall . "&RESPONSE-DATA-FORMAT=$responseEncoding";
    
    $resp   = simplexml_load_file($apiCall);
    $result = "";
    $result = $result . "<br><br><br><br><br>";
    $result = $result . "<br><br><br><br><br>";
    $result = $result . "<br><br><br><br><br>";
    $result = $result . "<br><br><br><br><br>";
    $result = $result . "<br><br><br><br><br>";
    $result = $result . "<br><br><br><br><br>";
    //$result .= "API: $apiCall<br>";       
    if ($resp && $resp->paginationOutput->totalEntries > 0) {
        $entries = $resp->paginationOutput->totalEntries;
        $result .= "<br><h1><center> $entries Results of $_POST[keyword] </h1><br>";
        $result .= '<table border="1" cellpadding="0" cellspacing="1" align ="center">';
        foreach ($resp->searchResult->item as $item) {
            $result .= "<tr>";
            if ($item->galleryURL) {
                $picURL = $item->galleryURL;
            } else {
                $picURL = "http://pics.ebaystatic.com/aw/pics/express/icons/iconPlaceholder_96x96.gif";
            }
            $result .= "<td><img src=\"$picURL\" ></td>";
            
            $link  = $item->viewItemURL;
            $title = $item->title;
            $result .= "<td><br>";
            $result .= "<a href=\"$link\">$title</a><br><br>";
            $condID = $item->condition->conditionId;
            if ($condID == "1000")
                $result .= "</b>Condition:</b> New";
            else if ($condID == "3000")
                $result .= "<b>Condition:</b> Used";
            else if ($condID == "4000")
                $result .= "<b>Condition:</b> Very Good";
            else if ($condID == "5000")
                $result .= "<b>Condition:</b> Good";
            else if ($condID == "6000")
                $result .= "<b>Condition:</b> Acceptable";
            else {
                $resCond = $item->condition->conditionDisplayName;
                $result .= "<b>Condition</b>: $resCond ";
            }
            $topRated = $item->topRatedListing;
            if ($topRated == "true")
                $result .= "<img src=\"itemTopRated.jpg\" height = 70px width = 90px> <br><br>";
            else
                $result .= "<br><br>";
            $listingType = $item->listingInfo->listingType;
            if ($listingType == "FixedPrice" || $listingType == "StoreInventory")
                $result .= "<b>Buy It Now</b><br><br>";
            if ($listingType == "Auction")
                $result .= "<b>Auction</b><br><br>";
            if ($listingType == "Classified")
                $result .= "<b>Classified Ad</b><br><br>";
            $acceptReturn = $item->returnsAccepted;
            if ($acceptReturn == "true")
                $result .= "Seller Accepts Return<br>";
            $shipChrg = "";
            if ($item->shippingInfo->shippingServiceCost != "")
                $shipChrg = $item->shippingInfo->shippingServiceCost;
            $shipType = $item->shippingInfo->shippingType;
            if (($shipChrg == 0) || $shipType == "Free")
                $result .= "Free Shipping -- ";
            $exptdShip = $item->shippingInfo->expeditedShipping;
            if ($exptdShip == "true")
                $result .= "Expedited Shipping Available -- ";
            
            $handlingTime = $item->shippingInfo->handlingTime;
            $result .= "Handled for Shipping in $handlingTime day(s)<br><br>";
            $itemCost = $item->sellingStatus->convertedCurrentPrice;
            $shipCost = $item->shippingInfo->shippingServiceCost;
            if ($shipCost > 0)
                $result .= "<b>Price: $$itemCost (+$$shipCost for shipping)</b> ";
            else
                $result .= "<b>Price: $$itemCost</b> ";
            $location = $item->location;
            $result .= "<i>From $location</i><br><br>";
            $result .= "</td>";
            $result .= "</tr>";
        }
        $result .= "</table>";
    } else {
        $result .= "<h1><center>No Result Found</center></h1>";
    }
}
?> 
  <div id = "results">
  <?php
echo "$result";
?>
  </div>  
 
</body>     
</html> 

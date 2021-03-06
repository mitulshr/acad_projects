<?php
   
   header('Acess-Control-Allow-Origin: *');
   header('Acess-Control-Allow-Method: GET,POST');
   $result = "";
   $apiCall = '';
   $resp;
   $json = '';
   $flag =1;
   $index = 0;
   $endpoint = 'http://svcs.ebay.com/services/search/FindingService/v1';  // URL to call
   $responseEncoding = 'XML';
   $appID = 'USC0098a7-f39a-485d-9653-1f8fb04952a';
   $safeKeyword = urlencode (utf8_encode($_GET['keyword']));
   $apiCall = "$endpoint?OPERATION-NAME=findItemsAdvanced"
               . "&siteid=0"
               . "&SERVICE-VERSION=1.0.0"
               . "&SECURITY-APPNAME=$appID"
               . "&keywords=$safeKeyword";
   if(!empty($_GET['rangemin']))
   {
       $min = $_GET['rangemin'];
       $apiCall = $apiCall . "&itemFilter($index).name=MinPrice";
       $apiCall = $apiCall . "&itemFilter($index).value=$min";
       $index++;
   }
   if(!empty($_GET['rangemax']))
   {
       $max = $_GET['rangemax'];
       $apiCall = $apiCall . "&itemFilter($index).name=MaxPrice";
       $apiCall = $apiCall . "&itemFilter($index).value=$max";
       $index++;
   }
                
   if(isset($_GET['cond']))
   {
       $condition = $_GET['cond'];           
       $apiCall = $apiCall . "&itemFilter($index).name=Condition";
       $condIndex = 0;
       for($i = 0 ; $i < count($condition) ; $i++)
       {
           if($condition[$i] == "new")
           {
              $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=1000";
              $condIndex++;
           }
         
           if($condition[$i] == "used")
           {
              $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=3000";
              $condIndex++;
           }
           
           if($condition[$i] == "verygood")
           {
              $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=4000";
              $condIndex++;
           }    
          
           if($condition[$i] == "good")
           {
              $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=5000";
              $condIndex++;
           }
            
           if($condition[$i] == "acceptable")
           {
              $apiCall = $apiCall . "&itemFilter($index).value($condIndex)=6000";
              $condIndex++;
           }       
       }
      $index++;
    }
        
       
    if(isset($_GET['buyformat']))
    {
        $buyformat = $_GET['buyformat'];
        $buyIndex = 0;
        $apiCall = $apiCall . "&itemFilter($index).name=ListingType";
        for($j = 0 ; $j < count($buyformat) ; $j++)
        {
                if($buyformat[$j] == "now")
                {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=FixedPrice";
                $buyIndex++;
                }
            
                if($buyformat[$j] == "auction")
                {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=Auction";
                $buyIndex++;
                }  
              
                if($buyformat[$j] == "ads")
                {
                $apiCall = $apiCall . "&itemFilter($index).value($buyIndex)=Classified";
                $buyIndex++;
                }     
           
        }
        $index++;
    }
       
    if(isset($_GET['seller']))
    {   
         $apiCall = $apiCall . "&itemFilter($index).name=ReturnsAcceptedOnly";
         $apiCall = $apiCall . "&itemFilter($index).value=true"; 
         $index++; 
    }
    
      
    if(isset($_GET['shipping']))
    {
          $shipping = $_GET['shipping'];
           for($k = 0 ; $k < count($shipping) ; $k++)
           {
                if($shipping[$k] == "freeship")
                  {
                        $apiCall = $apiCall . "&itemFilter($index).name=FreeShippingOnly";
                        $apiCall = $apiCall . "&itemFilter($index).value=true"; 
                        $index++;
                  }   
                if($shipping[$k] == "expiteship")
                  {
                        $apiCall = $apiCall . "&itemFilter($index).name=ExpeditedShippingType";
                        $apiCall = $apiCall . "&itemFilter($index).value=Expedited"; 
                        $index++;
                  } 
           }
       }
    
    if(!empty($_GET['shipdays']))
       {  
            $shipdays = $_GET['shipdays']; 
            $apiCall = $apiCall . "&itemFilter($index).name=MaxHandlingTime";
            $apiCall = $apiCall . "&itemFilter($index).value=$shipdays"; 
            $index++; 
       }       
   
   $sort = $_GET['sort'];
   $apiCall = $apiCall . "&sortOrder";
   $apiCall = $apiCall . "=$sort";
   $apiCall .= '&outputSelector[1]=SellerInfo';
   $apiCall .= '&outputSelector[2]=PictureURLSuperSize';
   $apiCall .= '&outputSelector[3]=StoreInfo';
   $itemsPerPage = intval($_GET['resperpg']); 
   $pageNumber = intval($_GET['pageNumber']); 
    
   //$apiCall = $apiCall . "&itemFilter($index).name=paginationInput.entriesPerPage";
   $apiCall = $apiCall . "&paginationInput.entriesPerPage=$itemsPerPage";  
   $apiCall = $apiCall . "&paginationInput.pageNumber=$pageNumber";         
   //$index++;     
   $apiCall = $apiCall . "&RESPONSE-DATA-FORMAT=$responseEncoding";
   $resp = simplexml_load_file($apiCall);
   if(intval($resp->paginationOutput->totalEntries) == 0)
   {
      $json .= '{"ack": "No results found"}';
      echo $json;
   }
   else
   {
        $entries = intval($resp->paginationOutput->totalEntries);
        $pgNum = intval($resp->paginationOutput->pageNumber);
        $perPg = intval($resp->paginationOutput->entriesPerPage);
  
        $json .= '{';
        $json .= '"ack":';
        $json .= '"'. $resp->ack .'",';
        $json .= '"resultCount":';
        $json .= '"'. $entries . '",';
        $json .= '"pageNumber":';
        $json .= '"' . $pgNum . '",';
        $json .= '"itemCount":';
        $json .= '"'.  $perPg .'",';


        if( $entries < $perPg )
                $itr = $entries;
        else
                $itr = $perPg;  
     
        $reqPg = ceil($entries / $perPg);
  
        if($reqPg == $pgNum)
                $itr =  $entries - (($pgNum-1) * $perPg);   
  
        for($i = 0; $i < $itr ; $i++)
        {
                if($i != 0)
                        $json .= ',';
                $json .= '"item'.$i.'":{';
                $json .= '"basicInfo":{';
                        $json .= '"title":';
                        $ttl = $resp->searchResult->item[$i]->title;
                        $encodedTitle = str_replace('"','\"',$ttl);
                        $json .=   '"'.$encodedTitle .'",';
                        $json .= '"viewItemURL":';
                        $json .= '"'. $resp->searchResult->item[$i]->viewItemURL  .'",';
                        $json .= '"galleryURL":';
                        $json .= '"'. $resp->searchResult->item[$i]->galleryURL  .'",';
                        $json .= '"pictureURLSuperSize":';
                        $json .= '"'. $resp->searchResult->item[$i]->pictureURLSuperSize  .'",';
                        $json .= '"convertedCurrentPrice":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellingStatus->convertedCurrentPrice  .'",';
                        $json .= '"shippingServiceCost":';
                        $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->shippingServiceCost  .'",';
                        $json .= '"conditionDisplayName":';
                        $json .= '"'. $resp->searchResult->item[$i]->condition->conditionDisplayName  .'",';
                        $json .= '"listingType":';
                        
                        if(($resp->searchResult->item[$i]->listingInfo->listingType) == "FixedPrice" || ($resp->searchResult->item[$i]->listingInfo->listingType) == "StoreInventory")
                                $json .= '"'. 'Buy It Now'  .'",';
                        else if(($resp->searchResult->item[$i]->listingInfo->listingType) == "Classified" )
                                $json .= '"'. 'Classified Ad'  .'",';
                        else
                                $json .= '"'. $resp->searchResult->item[$i]->listingInfo->listingType  .'",';
                        
                        $json .= '"location":';
                        $json .= '"'. $resp->searchResult->item[$i]->location  .'",';
                        $json .= '"categoryName":';
                        $json .= '"'. $resp->searchResult->item[$i]->primaryCategory->categoryName .'",';
                        $json .= '"topRatedListing":';
                        $json .= '"'. $resp->searchResult->item[$i]->topRatedListing .'"';
                $json .= '},'; 
                
                $json .= '"sellerInfo":{';
                        $json .= '"sellerUserName":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellerInfo->sellerUserName .'",';
                        $json .= '"feedbackScore":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellerInfo->feedbackScore .'",';
                        $json .= '"positiveFeedbackPercent":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellerInfo->positiveFeedbackPercent .'",';
                        $json .= '"feedbackRatingStar":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellerInfo->feedbackRatingStar .'",';
                        $json .= '"topRatedSeller":';
                        $json .= '"'. $resp->searchResult->item[$i]->sellerInfo->topRatedSeller .'",';  
                        $json .= '"sellerStoreName":';
                        $json .= '"'. $resp->searchResult->item[$i]->storeInfo->storeName .'",';    
                        $json .= '"sellerStoreURL":';
                        $json .= '"'. $resp->searchResult->item[$i]->storeInfo->storeURL .'"'; 
                $json .= '},';      
                
                $json .= '"shippingInfo":{'; 
                        $json .= '"shippingType":';
                        $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->shippingType .'",';
                        $json .= '"shipToLocations":';
                        
                        if($resp->searchResult->item[$i]->shippingInfo->shipToLocations == "")
                           $json .=  '"N/A",';
                        else
                           $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->shipToLocations .'",';
                        
                        //foreach($resp->searchResult->item[$i]->shippingInfo->shipToLocations as $loc)
                           // $locan .= $loc . ',';
                        //$json .= '"'. $locan .'",';
                        
                        $json .= '"expeditedShipping":';
                        $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->expeditedShipping .'",';
                        $json .= '"oneDayShippingAvailable":';
                        $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->oneDayShippingAvailable .'",';
                        $json .= '"returnsAccepted":';
                        $json .= '"'. $resp->searchResult->item[$i]->returnsAccepted .'",';
                        $json .= '"handlingTime":';
                        $json .= '"'. $resp->searchResult->item[$i]->shippingInfo->handlingTime .'"';
                $json .= '}';
                            
     $json .= '}';    
    }
  $json .= '}';
  echo $json;
  }
?>

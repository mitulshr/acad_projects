var i;
var j = 1;
var totalres = 0;
var itmperpg = 0;
var validator;


window.fbAsyncInit = function() {
        FB.init({
          appId      : '803058723098436',
          xfbml      : true,
          version    : 'v2.3'
        });
      };

      (function(d, s, id)
      {
         var js, fjs = d.getElementsByTagName(s)[0];
         if (d.getElementById(id)) 
            {return;}
         js = d.createElement(s); js.id = id;
         js.src = "//connect.facebook.net/en_US/sdk.js";
         fjs.parentNode.insertBefore(js, fjs);
       }
     (document, 'script', 'facebook-jssdk'));
    
   
  function postfb(obj,itm)
  {
    var k = $(obj).attr("id");
    var price_fb = itm[k]["basicInfo"]["convertedCurrentPrice"];
    var title_fb = itm[k]["basicInfo"]["title"];
    var img_fb = itm[k]["basicInfo"]["galleryURL"];
    var loc_fb = itm[k]["basicInfo"]["location"];
    var desc_fb = ''; 
    var ship_fb;
    var shipcost_fb = itm[k]["basicInfo"]["shippingServiceCost"];     
    
    if(parseInt(shipcost_fb) > 0)
     ship_fb = '&nbsp;(+ $' +shipcost_fb +'&nbsp;for shipping)';
    else
      ship_fb = '&nbsp;(FREE Shipping)';
      
    var desc_fb_ = 'Price: $'+ price_fb + ship_fb+'&nbsp;&nbsp;Location: &nbsp;'+loc_fb;   
    
    
    FB.ui(
    {
     method: 'feed',
     href: 'https://developers.facebook.com/docs/',
     picture: img_fb,
     name:title_fb,
     description: desc_fb_, //'Keep the shipping cost and shits',
     caption: 'Search Information from eBay.com',
     message:''
    },
    function(response) 
     {
        if (response && !response.error_code) 
        {
            alert('Posted Successfully.');
        } 
        else 
        {
            alert('Not Posted.');
        }
    }
   );
 
 }
 
 function loadNewPage(k,currPage)
{
  
         $("#myForm input[name=pageNumber]").val(k);
                    
         $.ajax
               ({
                 type: "GET",
                 url: "hw8.php",
                 data: $("#myForm").serialize(), // serializes the form's elements.
                 success: function(resp)
                      { 
                         doCreate(resp);
                       }
               });
                    

}

function forPaging(cur,counter)
{
  var currPage = $("#myForm input[name=pageNumber]").attr("value"); 
         
         
                  if($(cur).attr("id") == "pg1")
                   {
                    
                    if(j == currPage)
                      return false;
                    loadNewPage(j,currPage);
                   }
                  
                  if($(cur).attr("id") == "pg2")
                   {
                    if((j+1) == currPage)
                      return false;
                    loadNewPage(j+1,currPage);  
                   }
                 
                 
                 
                  if($(cur).attr("id") == "pg3")
                   {
                    if((j+2) == currPage)
                      return false;
                    loadNewPage(j+2);
                   }
                   
                  if($(cur).attr("id") == "pg4")
                   {
                    if((j+3) == currPage)
                      return false;
                    loadNewPage(j+3);
                   }
                   
                  if($(cur).attr("id") == "pg5")
                   {
                    
                    if((j+4) == currPage)
                      return false;
                    loadNewPage(j+4);
                   }   
                   
                  if($(cur).attr("id") == "next")
                   {
                     
                     
                         if(currPage % 5 == 1)
                        {
                          loadNewPage(j+1,currPage);
                        }    
                  
                        if(currPage % 5 == 2)
                         {
                           loadNewPage(j+2,currPage);  
                         }
                 
                 
                        if(currPage % 5 == 3)
                         {
                           loadNewPage(j+3,currPage);  
                         }
                   
                        if(currPage % 5 == 4)
                         {
                           loadNewPage(j+4,currPage);  
                         }
                   
                        if(currPage % 5 == 0)
                         {
                           j = j+5;
                           loadNewPage(j,currPage);  
                           $("#pg1").html(j);
                           $("#pg2").html(j+1);
                           $("#pg3").html(j+2);
                           $("#pg4").html(j+3);
                           $("#pg5").html(j+4);
                         }
                     
                     
                     
                   }
                   
                  if($(cur).attr("id") == "prev")
                   {
                       if(currPage % 5 == 2)
                        {
                          loadNewPage(j,currPage);
                        }    
                  
                        if(currPage % 5 == 3)
                         {
                           loadNewPage(j+1,currPage);  
                         }
                 
                 
                        if(currPage % 5 == 4)
                         {
                           loadNewPage(j+2,currPage);  
                         }
                   
                        if(currPage % 5 == 0)
                         {
                           loadNewPage(j+3,currPage);  
                         }
                   
                        if(currPage % 5 == 1)
                         {
                           j = j-5;
                           loadNewPage(j+4,currPage);  
                           $("#pg1").html(j);
                           $("#pg2").html(j+1);
                           $("#pg3").html(j+2);
                           $("#pg4").html(j+3);
                           $("#pg5").html(j+4);
                         }
                   }
  
} 


 
function doCreate(resp)
{
  
               //console.log(resp);
               resp = jQuery.parseJSON(resp);
               if(resp)
               { 
                 
                 //alert("Gotcha"); // show response from the php script.
                 //alert(resp.ack);
                 
                 var count = parseInt(resp.itemCount);
                 if((resp.ack).localeCompare("Success") == -1)
                  {
                   $("#result").html('<h2 style = "font-weight: bolder;">No Result Found</h2>'); 
                   return;
                  }
                 
                 var pgnumb = resp.pageNumber;
                 totalres = resp.resultCount;
                 itmperpg = count;
                 var itr = count;
                 var reqPg = Math.ceil(totalres/itmperpg);
                 var start = (parseInt (count) * (parseInt (pgnumb) - 1 ))  + 1;
                  
                 if(parseInt (totalres) < parseInt (count))
                   {
                     itr = totalres;
                   }
                 var end = (parseInt (pgnumb)) * itr; 
                 if(reqPg == parseInt(pgnumb))
                   {
                    itr = parseInt(totalres) - ((parseInt(pgnumb)-1) * parseInt(itmperpg));
                    end = parseInt(totalres); 
                   }
                 var item = [];
                 
                 for(i = 0 ; i < itr ;i++)
                  {
                    item[i] = resp["item"+i];
                    
                  }
                 
                 var htmlContent = '<div class = "container"><div ><br><div class = "media">';
                 htmlContent += '<h2>'+start + '-' + end + '&nbsp;items out of ' + totalres+'</h2><hr>';
                 for(i = 0; i < itr ; i++)
                   {
                     htmlContent += '<div class="media-left">';
                     var imgsrc = item[i]["basicInfo"]["galleryURL"];
                     var title = item[i]["basicInfo"]["title"];
                     var img
                     if(item[i]["basicInfo"]["pictureURLSuperSize"] == "")
                        img = item[i]["basicInfo"]["galleryURL"];
                     else
                        img =    item[i]["basicInfo"]["pictureURLSuperSize"];
                     
                     
                     //htmlContent += '<a href = "#demo'+i+'"><img class="media-object" data-toggle="modal" data-target="#myModal'+i+'" src = "' + imgsrc + '" height = 80 width = 80></a>'; //Shifted a /div at the end
                     
                     
                     
                    htmlContent+= '<a data-toggle="modal" data-target="#myModal'+i+'" href = "#demo'+i+'"><img class="media-object" src = "'+imgsrc+'" height = 80 width = 80"></a>';
                     htmlContent += '<div id="myModal'+i+'" class="modal fade">';
                     htmlContent += '    <div class="modal-dialog">';
                     htmlContent += '       <div class="modal-content">';
                     htmlContent += '         <div class="modal-header">';
                     htmlContent += '             <h4 class="modal-title">'+title+'</h4>';
                     htmlContent += '         </div>';
                     htmlContent += '         <div class="modal-body">';
                     htmlContent += '             <img src="'+img+'" style= "padding-left: 1.5cm; width: 90%;">';
                     htmlContent += '         </div>';
                     htmlContent += '        </div>';
                     htmlContent += '    </div>';   
                     htmlContent += '  </div>';
                     htmlContent += '</div>';                    
                     var link = item[i]["basicInfo"]["viewItemURL"];
                     htmlContent += '<div class="media-body"> <a target="_blank" href = "'+ link + '"> <b><h4 style = "font-weight: bolder;" class="media-heading">' + title + '</h4></b></a>';          
                     var price = item[i]["basicInfo"]["convertedCurrentPrice"];
                     var shipcost = item[i]["basicInfo"]["shippingServiceCost"];
                     htmlContent += '<p><b>Price:$'+price +'</b>&nbsp;';          
                     if(shipcost > 0)
                        htmlContent += '(+ $' +shipcost +'&nbsp;for shipping)&nbsp;&nbsp;&nbsp;';
                     else
                        htmlContent += '(FREE Shipping)&nbsp;&nbsp;&nbsp;';    
                     var loc = item[i]["basicInfo"]["location"];
                     htmlContent += 'Location:&nbsp;'+loc +'&nbsp;&nbsp;&nbsp;'; 
                     var itemrate = item[i]["basicInfo"]["topRatedListing"];
                     if(itemrate == "true")
                       htmlContent+='<img height = 30 width =40 src = "http://cs-server.usc.edu:45678/hw/hw8/itemTopRated.jpg">&nbsp;&nbsp;';
                     htmlContent += '<span data-toggle="collapse" data-target="#demo'+i+'"><a> View Details</a></span>&nbsp;&nbsp;';
                     htmlContent +='<span id = "'+i+'" class = "fblink"><a href="#"><img height = 20 width =20 src = "http://cs-server.usc.edu:45678/hw/hw8/fb.png"></a></span>';
                     htmlContent += '<div id="demo'+i+'"class="collapse">';

                     htmlContent +='<br><div class="bs-example">';
                     htmlContent +='   <ul class="nav nav-tabs"> ';
                     htmlContent +='    <li class="active"> <a data-toggle="tab" href="#basic'+i+'">Basic Info</a></li>';
                     htmlContent +='    <li> <a data-toggle="tab" href="#seller'+i+'">Seller Info</a></li> ';
                     htmlContent +='    <li><a data-toggle="tab" href="#shipping'+i+'">Shipping Info</a></li>';
                     htmlContent +='   </ul>';
                     htmlContent +=' <div class="tab-content">';
                     htmlContent +='   <div id="basic'+i+'" class="tab-pane fade in active"> ';
                     var catname = item[i]["basicInfo"]["categoryName"];
                     htmlContent +='    <div class="row"><div class = "col-sm-3"><b>Category name</b></div><div class = "col-sm-9">'+catname+'</div></div>';
                     var cond = item[i]["basicInfo"]["conditionDisplayName"];
                     htmlContent +='    <div class="row"><div class = "col-sm-3"><b>Condition</b></div><div class = "col-sm-9">'+cond+'</div></div>';
                     var buyfmt = item[i]["basicInfo"]["listingType"];
                     htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Buying format</b></div><div class = "col-sm-9">'+buyfmt+'</div></div> ';
                     htmlContent +='   </div>';
                     htmlContent +='   <div id="seller'+i+'" class="tab-pane fade">';
                     var usrname = item[i]["sellerInfo"]["sellerUserName"];
                     htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>User name</b></div><div class = "col-sm-9">'+usrname+'</div></div> ';
                     var feedscr = item[i]["sellerInfo"]["feedbackScore"];
                     htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Feedback score</b></div><div class = "col-sm-9">'+feedscr+'</div></div> ';
                     var feedpos = item[i]["sellerInfo"]["positiveFeedbackPercent"];
                     htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Positive feedback</b></div><div class = "col-sm-9">'+feedpos+'</div></div> ';
                     var feedrate = item[i]["sellerInfo"]["feedbackRatingStar"];
                     htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Feedback rating</b></div><div class = "col-sm-9">'+feedrate+'</div></div> ';
                     var toprate = item[i]["sellerInfo"]["topRatedSeller"];
                     if(toprate == "true")
                        htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>Top rated</b> </div><div class = "col-sm-9"><span class="glyphicon glyphicon-ok" style="color:green"></span></div></div> ';
                     else
                        htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Top rated</b> </div><div class = "col-sm-9"><span class="glyphicon glyphicon-remove" style="color:red"></span></div></div> ';
                     var stornam = item[i]["sellerInfo"]["sellerStoreName"];
                     var storlnk = item[i]["sellerInfo"]["sellerStoreURL"];
                     if(stornam == "")
                        stornam = 'N.A';
                     if(storlnk == '')    
                        htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>Store</b></div><div class = "col-sm-9">'+stornam+'</div></div> ';
                     else
                        htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Store</b></div><div class = "col-sm-9"><a href ="'+storlnk+'">'+stornam+'</a></div></div> ';
                     htmlContent +='   </div>';
                     htmlContent +='   <div id="shipping'+i+'" class="tab-pane fade">';
                     var shiptype = item[i]["shippingInfo"]["shippingType"];
                     htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>Shipping type</b></div><div class = "col-sm-9">'+shiptype+'</div></div> ';
                     var handltm = item[i]["shippingInfo"]["handlingTime"];
                     if(handltm == "")
                        htmlContent +='    <div class="row"><div class = "col-sm-3">  <b>Handling time</b></div><div class = "col-sm-9">N.A</div></div> ';
                     else
                        htmlContent +='    <div class="row"><div class = "col-sm-3">  <b>Handling time</b></div><div class = "col-sm-9">'+handltm+'&nbsp;day(s)</div></div> ';
                     var shploc = item[i]["shippingInfo"]["shipToLocations"];
                     htmlContent +='   <div class="row"><div class = "col-sm-3">  <b>Shipping location</b></div><div class = "col-sm-9">'+shploc+'</div></div> ';
                     var expship = item[i]["shippingInfo"]["expeditedShipping"];
                     if(expship == "true")
                        htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>Expedited shipping</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-ok" style="color:green" ></span></div></div> ';
                     else
                        htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>Expedited shipping</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-remove" style="color:red"></span></div></div>';
                     
                     var oneday = item[i]["shippingInfo"]["oneDayShippingAvailable"];
                      if(oneday == "true")
                        htmlContent +='    <div class="row"><div class = "col-sm-3"> <b>One day shipping</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-ok" style="color:green" ></span></div></div> ';
                     else
                        htmlContent +='     <div class="row"><div class = "col-sm-3"><b>One day shipping</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-remove" style="color:red"></span></div></div>';
                     
                     var rtnacc = item[i]["shippingInfo"]["returnsAccepted"];
                      if(rtnacc == "true")
                        htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Return accepted</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-ok" style="color:green"></span></div></div> ';
                     else
                        htmlContent +='     <div class="row"><div class = "col-sm-3"><b>Return accepted</b></div><div class = "col-sm-9"><span class="glyphicon glyphicon-remove" style="color:red"></span></div></div>';
                     htmlContent +='   </div>';
                     htmlContent +=' </div>';
                     htmlContent +='</div>';               
                     htmlContent += '</div>';
                     htmlContent += '</p></div><br>' 
                      
                   } 
                   
                   var curpg =  $("#myForm input[name=pageNumber]").attr("value");
                   
                   htmlContent += '<div id = "pag" > <nav>';
                   htmlContent += '<ul class="pagination">';
                   if( curpg > 1)
                        htmlContent += '<li class = "paging" id = "prev">';
                   else
                       htmlContent += '<li class="disabled">';
                   htmlContent += '<a  href="#result"  aria-label="Previous">';
                   htmlContent += '<span aria-hidden="true">&laquo;</span>';
                   htmlContent += '</a>';
                   htmlContent += '</li>';
                   var reqPg = Math.ceil(totalres/itmperpg);
                   
                   if(curpg == j)
                        {
                         
                         htmlContent += '<li class="active"><a class = "paging" id = "pg1" href="#result">'+j+'</a></li>';
                        }
                   else
                       htmlContent += '<li><a class = "paging" id = "pg1" href="#result">'+j+'</a></li>';
                   if(reqPg >= j+1)
                   {
                        if(curpg == j+1)
                                htmlContent += '<li class="active"><a class = "paging" id = "pg2" href="#result">'+(j+1)+'</a></li>';
                        else
                                htmlContent += '<li><a class = "paging" id = "pg2" href="#result">'+(j+1)+'</a></li>';                        
                   }
                   else
                    htmlContent += '<li class="disabled"><a href="#result">'+(j+1)+'</a></li>';
                   
                   if(reqPg >= j+2)
                   {
                        if(curpg == j+2)
                           htmlContent += '<li class="active"><a class = "paging" id = "pg3" href="#result">'+(j+2)+'</a></li>';
                        else
                           htmlContent += '<li><a class = "paging" id = "pg3" href="#result">'+(j+2)+'</a></li>';
                   }
                   else
                      htmlContent += '<li class="disabled"><a href="#result">'+(j+2)+'</a></li>';
                     
                   
                   if(reqPg >= j+3)
                   {
                        if(curpg == j+3)
                          htmlContent += '<li class="active"><a class = "paging" id = "pg4" href="#result">'+(j+3)+'</a></li>';     
                        else
                          htmlContent += '<li><a class = "paging" id = "pg4" href="#result">'+(j+3)+'</a></li>';
                   }
                   else
                       htmlContent += '<li class = "disabled"><a  href="#result">'+(j+3)+'</a></li>';
                   
                   if(reqPg >= j+4)
                   {
                        if(curpg == j+4)
                                htmlContent += '<li class="active"><a class = "paging" id = "pg5" href="#result">'+(j+4)+'</a></li>';
                        else
                                htmlContent += '<li><a class = "paging" id = "pg5" href="#result">'+(j+4)+'</a></li>';
                   }
                   else
                      htmlContent += '<li class = "disabled"><a href="#result">'+(j+4)+'</a></li>';
                   if(reqPg >= j+5)
                        htmlContent += '<li>';
                   else
                        htmlContent += '<li class="disabled">';
                   htmlContent += '<a class = "paging" id = "next" href="#result"  aria-label="Next">';
                   htmlContent += '<span class = "paging" aria-hidden="true">&raquo;</span>';
                   htmlContent += '</a>';
                   htmlContent += '</li>';
                   htmlContent += '</ul>';
                   htmlContent += '</nav>';
                   htmlContent += '</div></div></div></div>';
                   
                   $("#result").html(htmlContent); 
                }
                 
               else     
                   alert("Unable to connect. Please try again!!");
              
               $(".paging").click(function()
                {
                       forPaging($(this),j);           
                  
                });
               
               
               
               $(".fblink").click(function()
               {
                  
                  postfb(this,item);
                
               }); 
              
 }



$.validator.addMethod("greaterThan",

function (value, element, param) {
  var $element = $(element)
      , $min;
  if (typeof(param) === "string") {
      $min = $(param);
  } else {
  	  $min = $("#" + $element.data("min"));
  }
  if(!(parseFloat(value)) || !(parseFloat($min.val())))
     return true
  if (this.settings.onfocusout) {
    $min.off(".validate-greaterThan").on("blur.validate-greaterThan", function () {
      $element.valid();
    });
  }
  return parseFloat(value) >= parseFloat($min.val());
}, "Maximum value must be greater than the minimum value");


$(document).ready(function() 
 {
  
  validator =  $("#myForm").validate(
      {
        
        errorClass: "my-error-class",
        validClass: "my-valid-class",
       
       rules: 
        {
          keyword: "required",
          rangemin: 
                {
                number: true,
                min: 0
                },
          rangemax: 
                {
                number: true,
                min: 0,
                greaterThan: "#min"      
                },
          shipdays: 
                {
                digits: true,
                min: 1
                }
        },
             
        errorPlacement: function(error, element) {
            if(element.parent('.input-group').length) {
                error.insertAfter(element.parent());
            } else {
                error.insertAfter(element);
            }
        },
    highlight: function(element, errorClass, validClass) 
        {              $(element).closest('.form-group').addClass('has-error');
        },  
    unhighlight: function(element, errorClass, validClass) 
        {
              $(element).closest('.form-group').removeClass('has-error');
        },    
    errorElement: 'span',
    errorClass: 'help-block',    
   submitHandler: function(form)
   //$("#myForm").on('submit',function() 
   {
    $.ajax
        ({
           type: "GET",
           url: "hw8.php",
           data: $("#myForm").serialize(), // serializes the form's elements.
           //dataType: 'json',

           success: function(resp)
              {
                  
                  doCreate(resp);
              }
        }); // ajax
    return false;
  },
  
   messages: 
        {
          keyword: "Keyword is mandatory",
          minrange: 
                {
                number: "Please enter an integer",
                min: "Minumum price should be greater than zero"
                },
          maxrange: 
                {
                number: "Please enter an integer",
                min: "Maximum price should be greater than zero",
                greaterThan: "Maximum price cannot be less than minimum price"
                },
          shipdays: 
                {
                digits: "Please enter a valid digit for max handling time",
                min: "Max handling time should be greater than or equal to 1"
                }
        }


 
 }); //validator
}); //document.ready

      
       function resetValues()
        {
          j =1;
          $("#myForm input[name=pageNumber]").val(1);
          validator.resetForm();
          $('.form-group').removeClass('has-error');
          $("#min").removeClass('has-error').removeClass('my-error-class');
          $("#max").removeClass('has-error').removeClass('my-error-class');
          $("#shipdays").removeClass('has-error').removeClass('my-error-class');
          $("#keyword").removeClass('has-error').removeClass('my-error-class');
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
          document.getElementById("result").innerHTML = "";        
        }
    

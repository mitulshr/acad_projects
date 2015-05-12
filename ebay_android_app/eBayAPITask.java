package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import static android.support.v4.app.ActivityCompat.startActivity;

/**
 * Created by mitul on 19/4/15.
 */
public class eBayAPITask extends AsyncTask<String,Void,String> {

    private static final String TAG = "API Task";
    private Context context;
    private MainActivity activity;

    public eBayAPITask(MainActivity activity){
        super();
        this.activity = activity;
        this.context = this.activity.getApplicationContext();
    }


    @Override
    protected String doInBackground(String... params) {

        try{
             Log.d(TAG, "Inside API Task Call: " + params[0] );
             String result  = eBayURLCall.downloadFromServer(params);
            Log.d(TAG, "API Task Return value: " + result );
            return result;

        }catch(Exception e) {
            return new String();
        }

    }

    @Override
    protected void onPostExecute(String result) {
        super.onPostExecute(result);
        Log.d(TAG,result);
        String ack;
        ArrayList<itemData> itemData = new ArrayList<itemData>();
        int resultCount;

        try{
            JSONObject respObj = new JSONObject(result);
            ack = respObj.getString("ack");
            resultCount = Integer.parseInt(respObj.getString("resultCount"));
            for(int i =0; i< 4;i++)
            {
                JSONObject item = respObj.getJSONObject("item" + i);
                JSONObject basicInfo = item.getJSONObject("basicInfo");

                String title = basicInfo.getString("title");
                String galleryURL = basicInfo.getString("galleryURL");
                String viewItemURL = basicInfo.getString("viewItemURL");
                String pictureURL = basicInfo.getString("pictureURLSuperSize");
                String price = basicInfo.getString("convertedCurrentPrice");
                String shipCost = basicInfo.getString("shippingServiceCost");
                String condition = basicInfo.getString("conditionDisplayName");
                String listType = basicInfo.getString("listingType");
                String location = basicInfo.getString("location");
                String categoryName = basicInfo.getString("categoryName");
                String topRatedListing = basicInfo.getString("topRatedListing");

                JSONObject sellerInfo = item.getJSONObject("sellerInfo");
                String sellerName = sellerInfo.getString("sellerUserName");
                String feedbackScore = sellerInfo.getString("feedbackScore");
                String postFeedback = sellerInfo.getString("positiveFeedbackPercent");
                String feedRating = sellerInfo.getString("feedbackRatingStar");
                String topRatedSeller = sellerInfo.getString("topRatedSeller");
                String storeName = sellerInfo.getString("sellerStoreName");
                String storeURL = sellerInfo.getString("sellerStoreURL");

                JSONObject shippingInfo = item.getJSONObject("shippingInfo");
                String shipType = shippingInfo.getString("shippingType");
                String shipLoc = shippingInfo.getString("shipToLocations");
                String expediteShip = shippingInfo.getString("expeditedShipping");
                String oneDay = shippingInfo.getString("oneDayShippingAvailable");
                String returnAcc = shippingInfo.getString("returnsAccepted");
                String time = shippingInfo.getString("handlingTime");

                Log.d("PostExec: ","Adding data to itemData");
                itemData.add(new itemData(resultCount,title,galleryURL,viewItemURL,pictureURL,price,shipCost,
                        condition,listType,location,categoryName,topRatedListing,
                        sellerName,feedbackScore,postFeedback,feedRating,topRatedSeller,
                        storeName,storeURL,shipType,shipLoc,expediteShip,oneDay,returnAcc,time));


            }




        }catch (JSONException e) {
               e.printStackTrace();
               ack = "Exception Occurred!!!";

        }

        //Intent intent = new Intent(context,ResultActivity.class);
        //intent.putExtra("mainActArg",ack);
        //context.startActivity(intent);
        Log.d("API Task: ","calling main activity");
        this.activity.setItems(itemData);
    }
}

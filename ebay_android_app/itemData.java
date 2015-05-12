package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.util.Log;

import java.io.Serializable;

/**
 * Created by mitul on 19/4/15.
 */
public class itemData implements Serializable {

    int resultCount;
    String title;
    String galleryURL;
    String viewItemURL;
    String pictureURL;
    String price;
    String shipCost;
    String condition;
    String listType;
    String location;
    String categoryName;
    String topRatedListing;
    String sellerName;
    String feedbackScore;
    String postFeedback;
    String feedRating;
    String topRatedSeller;
    String storeName;
    String storeURL;
    String shipType;
    String shipLoc;
    String expediteShip;
    String oneDay;
    String returnAcc;
    String time;




    public itemData(int resultCount, String title, String galleryURL, String viewItemURL, String pictureURL, String price, String shipCost, String condition, String listType, String location, String categoryName, String topRatedListing, String sellerName, String feedbackScore, String postFeedback,String feedRating, String topRatedSeller, String storeName, String storeURL, String shipType, String shipLoc, String expediteShip, String oneDay, String returnAcc, String time)
    {
        super();

        Log.d("itemData: ", "Initializing Vars");
        this.resultCount = resultCount;
        this.title = title;
        this.galleryURL = galleryURL;
        this.viewItemURL = viewItemURL;
        this.pictureURL = pictureURL;
        this.price = price;
        this.shipCost = shipCost;
        this.condition = condition;
        this.listType = listType;
        this.location = location;
        this.categoryName = categoryName;
        this.topRatedListing = topRatedListing;
        this.sellerName = sellerName;
        this.feedbackScore = feedbackScore;
        this.postFeedback = postFeedback;
        this.feedRating = feedRating;
        this.topRatedSeller = topRatedSeller;
        this.storeName = storeName;
        this.storeURL = storeURL;
        this.shipType = shipType;
        this.shipLoc = shipLoc;
        this.expediteShip = expediteShip;
        this.oneDay = oneDay;
        this.returnAcc = returnAcc;
        this.time = time;
    }

    public int getResultCount() {
        return  resultCount;
    }

    public void setResultCount(int resultCount) {
        this.resultCount = resultCount;
    }

    public String getTitle(){
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getGalleryURL(){
        return galleryURL;
    }
    public void setGalleryURL(String galleryURL){
        this.galleryURL = galleryURL;
    }


    public String getViewItemURL(){
        return viewItemURL;
    }
    public void setViewItemURL(String viewItemURL){
        this.viewItemURL = viewItemURL;
    }

    public String getPictureURL(){
        return pictureURL;
    }
    public  void setPictureURL(String pictureURL){
        this.pictureURL = pictureURL;
    }

    public String getPrice(){
        return price;
    }
    public void setPrice(String price){
        this.price = price;
    }

    public String getShipCost(){
        return shipCost;
    }
    public void setShipCost(String shipCost){
        this.shipCost = shipCost;
    }


    public String getCondition() {
        return condition;
    }

    public String getListType() {
        return listType;
    }

    public String getLocation() {
        return location;
    }

    public String getCategoryName() {
        return categoryName;
    }

    public String getTopRatedListing() {
        return topRatedListing;
    }

    public String getSellerName() {
        return sellerName;
    }

    public String getFeedbackScore() {
        return feedbackScore;
    }

    public String getPostFeedback() {
        return postFeedback;
    }

    public String getTopRatedSeller() {
        return topRatedSeller;
    }

    public String getFeedRating() {
        return feedRating;
    }

    public String getStoreName() {
        return storeName;
    }

    public String getStoreURL() {
        return storeURL;
    }

    public String getShipType() {
        return shipType;
    }

    public String getShipLoc() {
        return shipLoc;
    }

    public String getExpediteShip() {
        return expediteShip;
    }

    public String getOneDay() {
        return oneDay;
    }

    public String getReturnAcc() {
        return returnAcc;
    }

    public String getTime() {
        return time;
    }


}

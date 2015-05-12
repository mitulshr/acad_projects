package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;


public class DetailsActivity extends ActionBarActivity {

    iconTask imgFetch;
    TextView title,price,location;
    itemData item;
    ImageView icon;
    Button bt_basic;
    Button bt_seller;
    Button bt_ship;
    LinearLayout LL_basic;
    LinearLayout LL_seller;
    LinearLayout LL_ship;
    TextView tv_catName,tv_condition,tv_buyingFormat;
    TextView tv_sellerName,tv_feedScore,tv_feedPositive,tv_feedRating,tv_store;
    TextView tv_shipType,tv_time,tv_loc;
    ImageView  iv_shipTopRated,iv_expedite,iv_oneDay,iv_return;

    ImageView iv_fb,iv_toprated;
    Button bt_buyNow;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_details);

        price = (TextView) findViewById(R.id.d_price);
        location = (TextView) findViewById(R.id.d_location);

        bt_basic = (Button) findViewById(R.id.bt_basic);
        bt_seller = (Button) findViewById(R.id.bt_seller);
        bt_ship = (Button) findViewById(R.id.bt_shipping);
        LL_basic = (LinearLayout) findViewById(R.id.LL_basic);
        LL_seller = (LinearLayout) findViewById(R.id.LL_seller);
        LL_ship = (LinearLayout) findViewById(R.id.LL_shipping);
        tv_catName = (TextView) findViewById(R.id.bi_category);
        tv_condition = (TextView) findViewById(R.id.bi_condition);
        tv_buyingFormat = (TextView) findViewById(R.id.bi_buyFormat);
        tv_sellerName = (TextView) findViewById(R.id.sell_name);
        tv_feedScore = (TextView) findViewById(R.id.seller_feedScore);
        tv_feedPositive = (TextView) findViewById(R.id.seller_postiveFeedback);
        tv_feedRating = (TextView) findViewById(R.id.seller_rating);
        iv_shipTopRated = (ImageView) findViewById(R.id.seller_IV_topRated);
        tv_store = (TextView) findViewById(R.id.seller_store);
        tv_shipType = (TextView) findViewById(R.id.ship_type);
        tv_time = (TextView) findViewById(R.id.ship_time);
        tv_loc = (TextView) findViewById(R.id.ship_location);
        iv_expedite = (ImageView) findViewById(R.id.ship_TV_expedite);
        iv_oneDay = (ImageView) findViewById(R.id.ship_TV_oneDay);
        iv_return = (ImageView) findViewById(R.id.ship_TV_returnAccp);

        bt_buyNow = (Button) findViewById(R.id.d_buyNow);
        iv_fb = (ImageView) findViewById(R.id.d_fbIcon);
        iv_toprated = (ImageView) findViewById(R.id.d_topRate);


        LL_seller.setVisibility(LinearLayout.GONE);
        LL_ship.setVisibility(LinearLayout.GONE);

        bt_basic.setBackgroundColor(Color.argb(155, 185, 185, 185));

        bt_basic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(LL_basic.getVisibility() == View.VISIBLE)
                    return;
                else
                {
                    LL_seller.setVisibility(LinearLayout.GONE);
                    LL_ship.setVisibility(LinearLayout.GONE);
                    LL_basic.setVisibility(LinearLayout.VISIBLE);
                    bt_basic.setBackgroundColor(Color.argb(155, 185, 185, 185));
                    bt_seller.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    bt_ship.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    return;
                }
            }
        });

        bt_seller.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(LL_seller.getVisibility() == View.VISIBLE)
                    return;
                else
                {
                    LL_basic.setVisibility(LinearLayout.GONE);
                    LL_ship.setVisibility(LinearLayout.GONE);
                    LL_seller.setVisibility(LinearLayout.VISIBLE);
                    bt_basic.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    bt_seller.setBackgroundColor(Color.argb(155, 185, 185, 185));
                    bt_ship.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    return;
                }
            }
        });


        bt_ship.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(LL_ship.getVisibility() == View.VISIBLE)
                    return;
                else
                {
                    LL_basic.setVisibility(LinearLayout.GONE);
                    LL_seller.setVisibility(LinearLayout.GONE);
                    LL_ship.setVisibility(LinearLayout.VISIBLE);

                    bt_basic.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    bt_seller.setBackgroundColor(Color.argb(0, 185, 185, 185));
                    bt_ship.setBackgroundColor(Color.argb(155, 185, 185, 185));
                    return;
                }
            }
        });

        bt_buyNow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(android.content.Intent.ACTION_VIEW,
                Uri.parse(item.getViewItemURL()));
                startActivity(intent);
            }
        });


        this.imgFetch = new iconTask(this);
        item = (itemData) getIntent().getSerializableExtra("ResultActArg");

        title = (TextView) findViewById(R.id.d_title);
        title.setText(item.getTitle());

        if(item.getTopRatedListing().equals("false"))
        {
            iv_toprated.setVisibility(View.INVISIBLE);
        }

        if(item.getShipCost().equals("") || (Double.parseDouble(item.getShipCost()) == 0))
        {
            String temp = "Price:$" + item.getPrice() + "(FREE Shipping)";
            price.setText(temp);
        }
        else
        {
            String temp = "Price:$" + item.getPrice() + "(+ $" + item.getShipCost() + " Shipping)";
        }

        location.setText(item.getLocation());


        icon = (ImageView) findViewById(R.id.d_icon);
        if(item.getPictureURL() != null)
        {
            icon.setTag(item.getPictureURL());
            Log.d("details Activity: ", "Calling loadImage");
            Log.d("loadImage sending URL", (String) icon.getTag());


            new AsyncTask<Void,Void,Void>(){
                Drawable dw;
                @Override
                protected Void doInBackground(Void... params) {
                    String s_url = item.getPictureURL();
                    Log.d("ImagetAsk URL: ",s_url);
                    InputStream istr;
                    try {
                        Log.d("Icon Task", "Fetching: " + s_url);
                        URL url = new URL(s_url);
                        istr = url.openStream();
                    } catch (MalformedURLException e) {
                        Log.d("Icon Task: ", "Malformed: " + e.getMessage());
                        throw new RuntimeException(e);
                    } catch (IOException e)
                    {
                        Log.d("Icon Task", "I/O : " + e.getMessage());
                        throw new RuntimeException(e);

                    }
                    dw = Drawable.createFromStream(istr, "src");
                    return null;
                }

                @Override
                protected void onPostExecute(Void result) {
                    if(dw != null)
                        icon.setImageDrawable(dw);
                }
            }.execute();

        }


        tv_catName.setText(item.getCategoryName());
        tv_condition.setText(item.getCondition());
        tv_buyingFormat.setText(item.getListType());

        tv_sellerName.setText(item.getSellerName());
        tv_feedScore.setText(item.getFeedbackScore());
        tv_feedPositive.setText(item.getPostFeedback());
        tv_feedRating.setText(item.getFeedRating());
        if(item.getTopRatedSeller().equalsIgnoreCase("true"))
            iv_shipTopRated.setImageResource(R.mipmap.tick);
        else
            iv_shipTopRated.setImageResource(R.mipmap.cross);
        tv_store.setText(item.getStoreName());

        tv_shipType.setText(item.getShipType());
        tv_time.setText(item.getTime());
        tv_loc.setText(item.getShipLoc());

        if(item.getExpediteShip().equalsIgnoreCase("true"))
            iv_expedite.setImageResource(R.mipmap.tick);
        else
            iv_expedite.setImageResource(R.mipmap.cross);

        if(item.getOneDay().equalsIgnoreCase("true"))
            iv_oneDay.setImageResource(R.mipmap.tick);
        else
            iv_oneDay.setImageResource(R.mipmap.cross);

        if(item.getReturnAcc().equalsIgnoreCase("true"))
            iv_return.setImageResource(R.mipmap.tick);
        else
            iv_return.setImageResource(R.mipmap.cross);

    }




}

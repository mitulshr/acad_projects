package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;


public class ResultActivity extends ActionBarActivity {

    ListView itemList;
    LayoutInflater layoutInflater;
    iconTask imgFetch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d("ResultActivity: ", "Inside Result Activity");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
        ArrayList<itemData> itemData = (ArrayList<itemData>) getIntent().getSerializableExtra("mainActArg");
        this.layoutInflater = LayoutInflater.from(this);
        this.itemList = (ListView) findViewById(R.id.item_list);
        this.imgFetch = new iconTask(this);
        Log.d("ResultActivity: ","Calling Adapter");
        itemList.setAdapter(new ItemAdapter(this,this.imgFetch,this.layoutInflater,itemData));
        //String args = getIntent().getStringExtra("mainActArg");
        //TextView t = (TextView) findViewById(R.id.resultAPI);
        //t.setText(args);


    }

    public void switchContext(itemData itemData) {

            Log.d("ResultActivity: ","Inside switch Context");
            Intent intent = new Intent(ResultActivity.this,DetailsActivity.class);
            intent.putExtra("ResultActArg",itemData);
            Log.d("ResultActivity: ","Calling Details Activity");
            startActivity(intent);
    }
}
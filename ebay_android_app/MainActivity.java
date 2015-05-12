package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;


public class MainActivity extends ActionBarActivity {

    String[] sortBy;
    Spinner sp;
    Button searchButton;
    EditText ET_keywd;

    private static final String TAG = MainActivity.class.getSimpleName();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sp = (Spinner) findViewById(R.id.SP_sortBy);
        sortBy = getResources().getStringArray(R.array.sortByValues);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item,sortBy);
        sp.setAdapter(adapter);
        searchButton = (Button) findViewById(R.id.searchBtn);

        searchButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Call to API Class
                Log.d(TAG, "Calling API Task");
                eBayAPITask APItask = new eBayAPITask(MainActivity.this);
                try{
                    ET_keywd = (EditText) findViewById(R.id.ET_keyword);
                    String arg_keyword = ET_keywd.getText().toString();
                    Log.d(TAG, "Arguments as: " + arg_keyword);
                    APItask.execute(arg_keyword);
                }catch (Exception e) {
                       APItask.cancel(true);
                       alert("Task got Cancelled!!");
                }
            }
        });

    }

    public void alert(String s) {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_SHORT).show();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void setItems(ArrayList<itemData> itemData){
        Log.d("MainActivity: ","Called from API task");
        Intent intent = new Intent(MainActivity.this,ResultActivity.class);
        intent.putExtra("mainActArg",itemData);
        Log.d("MainActivity: ","Calling Result Activity");
        startActivity(intent);

        //TextView t = (TextView) findViewById(R.id.TV_result);
        //t.setText(ack);
    }

}

package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.BaseAdapter;
import android.widget.ImageView;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;

/**
 * Created by mitul on 20/4/15.
 */
public class iconTask {

    private HashMap<String, Drawable> imageCache;
    private static Drawable DEFAULT_ICON = null;
    private BaseAdapter adapt;


    public iconTask(Context ctx)
    {
        imageCache = new HashMap<String, Drawable>();
    }

    public Drawable loadImage(BaseAdapter adapt, ImageView view)
    {
        Log.d("LoadImage: ", "Inside Load Image");
        this.adapt = adapt;
        String url = (String) view.getTag();
        Log.d("logImage URl: ",url);
        if (imageCache.containsKey(url))
        {
            return imageCache.get(url);
        }
        else {
            new ImageTask().execute(url);
            return DEFAULT_ICON;
        }
    }

    private class ImageTask extends AsyncTask<String, Void, Drawable>
    {
        private String s_url;

        @Override
        protected Drawable doInBackground(String... params) {
            s_url = params[0];
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
            return Drawable.createFromStream(istr, "src");
        }

        @Override
        protected void onPostExecute(Drawable result) {
            super.onPostExecute(result);
            synchronized (this) {
                imageCache.put(s_url, result);
            }
            adapt.notifyDataSetChanged();
        }

    }
}

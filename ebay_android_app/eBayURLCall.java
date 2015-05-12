package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.util.Log;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.StatusLine;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

/**
 * Created by mitul on 20/4/15.
 */
public class eBayURLCall {
    private static final String fixedURL = "http://cs-server.usc.edu:65005/assignment8/hw8.php?" +
            "&rangemin=&rangemax=&shipdays=&sort=BestMatch&resperpg=5&pageNumber=1&search=search";
    private static final int HTTP_STATUS_OK = 200;
    private static byte[] buff = new byte[1024];

    public static class ApiException extends Exception {
        private static final long serialVersionUID = 1L;

        public ApiException (String msg)
        {
            super (msg);
        }

        public ApiException (String msg, Throwable thr)
        {
            super (msg, thr);
        }
    }
    protected static synchronized String downloadFromServer (String... params)
            throws ApiException, UnsupportedEncodingException {
        String retval = "";
        String keywrd = URLEncoder.encode(params[0], "utf-8");


        String finalURL = fixedURL
                + "&keyword=" + keywrd;

        Log.d("URLCall", "Fetching " + finalURL);

        // create an http client and a request object.
        HttpClient client = new DefaultHttpClient();
        Log.d("URLCall", "After HttpClient ");
        HttpGet request = new HttpGet(finalURL);
        Log.d("URLCall", "After HttpGet ");
        try {

            // execute the request
            HttpResponse response = client.execute(request);
            StatusLine status = response.getStatusLine();
            if (status.getStatusCode() != HTTP_STATUS_OK) {
                // handle error here
                throw new ApiException("Invalid response from ebay.com" +
                        status.toString());
            }

            // process the content.
            Log.d("URLCall", "Respone code is 200");
            HttpEntity entity = response.getEntity();
            retval  = EntityUtils.toString(entity);
            //InputStream ist = entity.getContent();
            //ByteArrayOutputStream content = new ByteArrayOutputStream();

            //int readCount = 0;
            //while ((readCount = ist.read(buff)) != -1) {
            //    content.write(buff, 0, readCount);
           // }
           // retval = new String (content.toByteArray());

        } catch (Exception e) {
            throw new ApiException("Problem connecting to the server " +
                    e.getMessage(), e);
        }
        Log.d("URLCall", "Retval\n " + retval);
        return retval;
    }

}

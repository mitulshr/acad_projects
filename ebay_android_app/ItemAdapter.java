package com.elasticbeanstalk.httpebaysearchproject.ebayproject;

import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

/**
 * Created by mitul on 19/4/15.
 */
public class ItemAdapter extends BaseAdapter implements View.OnClickListener {

    ResultActivity activity;
    LayoutInflater layoutInflater;
    ArrayList<itemData> items;
    iconTask imgFetch;

    public ItemAdapter(ResultActivity resultActivity, iconTask imgFetch, LayoutInflater layoutInflater, ArrayList<itemData> itemData) {
        Log.d("Adapter: ", "Inside adapter");
        this.activity = resultActivity;
        this.layoutInflater = layoutInflater;
        this.items = itemData;
        this.imgFetch = imgFetch;
    }

    @Override
    public int getCount() {
        return this.items.size();
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }



    public class MyViewHolder {
        public TextView itemTitle,itemPrice;
        public ImageView icon;
        public itemData itemData;
    }


    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Log.d("Adapter: ", "Inside getView");
        MyViewHolder holder;
        if (convertView == null) {
            Log.d("Adapter: ", "convertView is null");
            convertView = layoutInflater.inflate (R.layout.item_row, parent, false);
            holder = new MyViewHolder();
            holder.itemTitle = (TextView) convertView.findViewById(R.id.item_title);
            holder.itemPrice = (TextView) convertView.findViewById(R.id.item_price);
            holder.icon = (ImageView) convertView.findViewById(R.id.item_icon);
            convertView.setTag(holder);
        }
        else {
            Log.d("Adapter: ", "contentView is not null");
            holder = (MyViewHolder) convertView.getTag();
        }

        convertView.setOnClickListener(this);

        itemData itemsData = items.get(position);
        holder.itemData = itemsData;
        holder.itemTitle.setText(itemsData.getTitle());
        holder.itemPrice.setText(itemsData.getPrice());
        Log.d("Adapter: ", "Got all other data");
        if(itemsData.getPictureURL() != null) {
            holder.icon.setTag(itemsData.getPictureURL());
            Log.d("Adapter: ", "Calling loadImage");
            Log.d("loadImage sending URL", (String) holder.icon.getTag());
            Drawable dr = imgFetch.loadImage(this, holder.icon);
            if(dr != null) {
                holder.icon.setImageDrawable(dr);
            }
        }

        else {
            holder.icon.setTag(itemsData.getGalleryURL());
            Drawable dr = imgFetch.loadImage(this, holder.icon);
            if(dr != null) {
                holder.icon.setImageDrawable(dr);
            }
        }

        return convertView;
    }

    @Override
    public void onClick(View v) {
             MyViewHolder holder = (MyViewHolder) v.getTag();
             Log.d("ON CLICK : ", "Inside onClick");
             if(v instanceof TextView)
             {
                     Log.d("ON CLICK: ", "Inside ImageView");
                     Intent intent = new Intent(android.content.Intent.ACTION_VIEW,
                     Uri.parse(holder.itemData.getViewItemURL()));
                     this.activity.startActivity(intent);
             }
             if(v instanceof View)
             {
                 Log.d("ON CLICK: ", "Inside View->switchContext");
                 this.activity.switchContext(holder.itemData);
             }


    }
}

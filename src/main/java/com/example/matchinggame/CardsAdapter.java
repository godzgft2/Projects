package com.example.matchinggame;
// CardsAdapter.java
import android.animation.Animator;
import android.animation.AnimatorInflater;
import android.animation.ObjectAnimator;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;

import java.util.List;

public class CardsAdapter extends BaseAdapter {

    private Context context;
    private List<Integer> cardImages;
    private LayoutInflater inflater;

    public CardsAdapter(Context context, List<Integer> cardImages) {
        this.context = context;
        this.cardImages = cardImages;
        inflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return cardImages.size();
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = convertView;
        ViewHolder viewHolder;
        if (view == null) {
            view = inflater.inflate(R.layout.card_item_layout, parent, false);
            viewHolder = new ViewHolder();
            viewHolder.imageView = view.findViewById(R.id.image_card);
            view.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder) view.getTag();
        }

        int imageResource = cardImages.get(position);
        if (imageResource == R.drawable.ic_card_back) {
            // Set the back side image for cards that haven't been flipped yet
            viewHolder.imageView.setImageResource(R.drawable.ic_card_back);
        } else {
            // Set the front side image for cards that have been flipped
            viewHolder.imageView.setImageResource(imageResource);
        }
        return view;
    }


    public void flipCard(int position, int imageResource) {
        Animator flipAnimator;
        if (cardImages.get(position) == R.drawable.ic_card_back) {
            // Flip from back side to front side
            flipAnimator = AnimatorInflater.loadAnimator(context, R.animator.flip_in);
        } else {
            // Flip from front side to back side
            flipAnimator = AnimatorInflater.loadAnimator(context, R.animator.flip_out);
        }

        if (flipAnimator instanceof ObjectAnimator) {
            ObjectAnimator objectAnimator = (ObjectAnimator) flipAnimator;
            View cardView = getView(position, null, null); // Get the view of the card
            if (cardView != null) {
                ImageView imageView = cardView.findViewById(R.id.image_card); // Find the imageView
                if (imageView != null) {
                    objectAnimator.setTarget(imageView);
                    objectAnimator.start();
                }
            }
        } else {
            Log.e("FlipCard", "Failed to load ObjectAnimator");
        }

        cardImages.set(position, imageResource);
        notifyDataSetChanged();
    }






    private static class ViewHolder {
        ImageView imageView;
    }
    public boolean allCardsMatched() {
        for (int imageResource : cardImages) {
            if (imageResource == R.drawable.ic_card_back) {
                return false;
            }
        }
        return true;
    }
}



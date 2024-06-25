package com.example.matchinggame;

// MainActivity.java
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.graphics.drawable.TransitionDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final int NUM_PAIRS = 8;
    private static final int GRID_SIZE = 4;
    private static final String PREFS_NAME = "GameStats";
    private static final String KEY_WINS = "wins";
    private static final String KEY_LOSSES = "losses";
    private static final String KEY_PLAYED = "played";

    private SharedPreferences sharedPreferences;
    private int wins, losses, played;

    private List<Integer> cardImages;
    private List<Integer> flippedCards;
    private CardsAdapter cardsAdapter;
    private GridView gridViewCards;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sharedPreferences = getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        wins = sharedPreferences.getInt(KEY_WINS, 0);
        losses = sharedPreferences.getInt(KEY_LOSSES, 0);
        played = sharedPreferences.getInt(KEY_PLAYED, 0);

        gridViewCards = findViewById(R.id.grid_view_cards); // Initialize gridViewCards

        // Initialize card images
        cardImages = new ArrayList<>();
        for (int i = 0; i < NUM_PAIRS; i++) {
            cardImages.add(R.drawable.ic_card_back);
            cardImages.add(R.drawable.ic_card_back);
        }
        Collections.shuffle(cardImages);

        flippedCards = new ArrayList<>();

        cardsAdapter = new CardsAdapter(this, cardImages);
        gridViewCards.setAdapter(cardsAdapter);

        gridViewCards.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (flippedCards.size() < 2) {
                    flipCard(position);
                }
            }
        });
    }

    private void flipCard(int position) {
        if (!flippedCards.contains(position)) {
            int image = cardImages.get(position);
            // Check if the card is currently face down (showing the back side)
            if (image == R.drawable.ic_card_back) {
                // Flip the card to show the front side
                cardsAdapter.flipCard(position, getCardImage(position));
            } else {
                // The card is already face up (showing the front side), so ignore the click
                return;
            }
            flippedCards.add(position);

            if (flippedCards.size() == 2) {
                checkForMatch();
            }
        }
    }


    private void checkForMatch() {
        int firstCard = flippedCards.get(0);
        int secondCard = flippedCards.get(1);

        if (cardImages.get(firstCard).equals(cardImages.get(secondCard))) {
            // Match found
            Toast.makeText(this, "Match found!", Toast.LENGTH_SHORT).show();
        } else {
            // No match
            Toast.makeText(this, "No match, try again.", Toast.LENGTH_SHORT).show();
            // Flip the cards back after a short delay
            gridViewCards.postDelayed(new Runnable() {
                @Override
                public void run() {
                    cardsAdapter.flipCard(firstCard, R.drawable.ic_card_back);
                    cardsAdapter.flipCard(secondCard, R.drawable.ic_card_back);
                }
            }, 1000);
        }

        flippedCards.clear();

        // Check if all cards are matched
        if (cardsAdapter.allCardsMatched()) {
            wins++;
            ImageView imageView = findViewById(R.id.image_view);
            TransitionDrawable transitionDrawable = (TransitionDrawable) imageView.getDrawable();
            transitionDrawable.startTransition(1000); // Duration in milliseconds

            // Display a pop-up message indicating the win and showing game statistics
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Congratulations!");
            builder.setMessage("You Won!\n\nWins: " + wins);
            builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // Reset the game or perform any other action
                }
            });
            builder.show();
        }
    }

    private int getCardImage(int index) {
        // Calculate the index of the Pokemon image based on the card position
        int pokemonIndex = index % NUM_PAIRS; // Ensure it cycles through the available Pokemon images
        switch (pokemonIndex) {
            case 0:
                return R.drawable.charizard;
            case 1:
                return R.drawable.lugia;
            case 2:
                return R.drawable.blastoise;
            case 3:
                return R.drawable.aipom;
            case 4:
                return R.drawable.pikachu;
            case 5:
                return R.drawable.giratina;
            case 6:
                return R.drawable.groudon;
            case 7:
                return R.drawable.eevee;
            default:
                return R.drawable.ic_card_back;
        }
    }


    @Override
    protected void onPause() {
        super.onPause();
        // Update player statistics
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt(KEY_WINS, wins);
        editor.putInt(KEY_LOSSES, losses);
        editor.putInt(KEY_PLAYED, played);
        editor.apply();
    }
}

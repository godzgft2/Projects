package main

import (
	"fmt"
	"math/rand"
)

const DECKSIZE = 17
const PILESIZE = 5

// Provides useful functions to Card types such as checking if a card is next
// to another card in value or returning the name of value of a card
type Card interface {
	nextTo(Card) bool
	String() string
	getValue() int
}

// Struct for normal cards in the deck, gives name and value of card
type PlainCard struct {
	name  string
	value int
}

// Struct for wild cards, same variables as PlainCard
type WildCard struct {
	name  string
	value int
}

// Returns the name of the plain card
func (p PlainCard) String() string {
	return p.name
}

// Returns name of wild card
func (w WildCard) String() string {
	return w.name
}

// Returns value of plain card, ex. ace = 1, two = 2, etc
func (p PlainCard) getValue() int {
	return p.value
}

// Returns value of wild card
func (w WildCard) getValue() int {
	return w.value
}

// Checks if value of card is next to another card's value, also wraps around so 0 is next to 4
func (p PlainCard) nextTo(c Card) bool {
	if c.getValue() == 5 {
		return true
	}
	switch p.getValue() {
	case 1:
		if c.getValue() == 2 || c.getValue() == 4 {
			return true
		}
	case 2:
		if c.getValue() == 1 || c.getValue() == 3 {
			return true
		}
	case 3:
		if c.getValue() == 2 || c.getValue() == 4 {
			return true
		}
	case 4:
		if c.getValue() == 1 || c.getValue() == 3 {
			return true
		}
	}
	return false
}

// Returns true because wild card is always next to any card
func (w WildCard) nextTo(c Card) bool {
	return true
}

func main() {
	a := PlainCard{
		name:  "Ace of Clubs",
		value: 1,
	}
	b := PlainCard{
		name:  "Ace of Spades",
		value: 1,
	}
	c := PlainCard{
		name:  "Ace of Hearts",
		value: 1,
	}
	d := PlainCard{
		name:  "Ace of Diamonds",
		value: 1,
	}
	e := PlainCard{
		name:  "Two of Clubs",
		value: 2,
	}
	f := PlainCard{
		name:  "Two of Spades",
		value: 2,
	}
	g := PlainCard{
		name:  "Two of Hearts",
		value: 2,
	}
	h := PlainCard{
		name:  "Two of Diamonds",
		value: 2,
	}
	i := PlainCard{
		name:  "Three of Clubs",
		value: 3,
	}
	j := PlainCard{
		name:  "Three of Spades",
		value: 3,
	}
	k := PlainCard{
		name:  "Three of Hearts",
		value: 3,
	}
	l := PlainCard{
		name:  "Three of Diamonds",
		value: 3,
	}
	m := PlainCard{
		name:  "Four of Clubs",
		value: 4,
	}
	n := PlainCard{
		name:  "Four of Spades",
		value: 4,
	}
	o := PlainCard{
		name:  "Four of Diamonds",
		value: 4,
	}
	p := PlainCard{
		name:  "Four of Hearts",
		value: 4,
	}
	w := WildCard{
		name:  "Wild Card",
		value: 5,
	}

	deck := [DECKSIZE]Card{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, w}

	rand.Shuffle(DECKSIZE, func(i, j int) {
		deck[i], deck[j] = deck[j], deck[i]
	})

	pile := [PILESIZE]Card{deck[0], deck[1], deck[2], deck[3], deck[4]}
	pilepos := 0
	deckpos := 5
	var hidden int
	var choice int

	fmt.Println("One pile Solitaire")

	for pilepos < PILESIZE && deckpos < DECKSIZE {
		fmt.Println("Pile: ", pile[pilepos])
		hidden = 4 - pilepos
		for hidden > 0 {
			fmt.Println("Hidden")
			hidden--
		}
		fmt.Println("Card to Match: ", deck[deckpos])
		fmt.Println("1. Move from pile")
		fmt.Println("2. Draw from deck")
		fmt.Println("Choose move: ")
		fmt.Scan(&choice)
		switch choice {
		case 1:
			if pile[pilepos].nextTo(deck[deckpos]) {
				pilepos++
				deckpos++
			}
		case 2:
			deckpos++
		}
	}
	if pilepos == 5 {
		fmt.Println("Congratulations, you win!")
	} else {
		fmt.Println("Sorry you lost. Try again!")
	}
}

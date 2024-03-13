package com.example.dicegame


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import android.view.View
import com.example.dicegame.databinding.ActivityMainBinding
import kotlin.random.Random






class MainActivity : AppCompatActivity() {
    private lateinit var binding : ActivityMainBinding
    private lateinit var diceIds : Array<Int>
    private var currentDiceValue = 0

    private var totalPoints1 : Int = 0
    private var totalPoints2 : Int = 0
    private var totalJackpoints : Int = 5

    private var currentPlayer = 1  //starts with player 1
    private var currentPoints1 : Int = 0 //binding.player1_view.text = "Player 1 total: $currentPoints1"
    private var currentPoints2 : Int = 0 //binding.player2_view.text = "Player 2 total: $currentPoints2"
    private var jackpoint : Int = 5      //binding.jackpot_view.text = "Current Jackpot: $jackpoint"


    private var isDoublePoints = false   //for case 4
    private var isJackpotPoints = false  //for case 6


    private var isAnswered = true // Track whether the current question is answered


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        diceIds = arrayOf(
            R.drawable.diceface_1,
            R.drawable.diceface_2,
            R.drawable.diceface_3,
            R.drawable.diceface_4,
            R.drawable.diceface_5,
            R.drawable.diceface_6
        )

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Initialize current (these are local) player & jackpot points
        currentPoints1 = 0
        currentPoints2 = 0
        jackpoint = 5


        //show the current points
        binding.player1View.text = "Player 1 total: $currentPoints1"
        binding.player2View.text = "Player 2 total: $currentPoints2"
        binding.jackpotView.text = "Current Jackpot: $jackpoint"


        //Show the current player
        binding.currentplayView.text = "Current Player = $currentPlayer"


        binding.editText.visibility = View.GONE

        //So the user can't press the guess button until they input an answer
        binding.guessbutton.isEnabled = false

        binding.updatetextView.text = "Press the Roll Dice Button to Start!"

        binding.rolldiceButton.setOnClickListener {
            if(isAnswered == true) {
                rollDice()
            }
        }//end setOnClickListener


        binding.guessbutton.setOnClickListener {
            // Handle the guess button click
            checkAnswer()
        }

    }


    //set random dice value when a user clicks the roll dice button
    private fun rollDice(){
        binding.updatetextView.text = "Roll the Dice"
        isAnswered = false // Set to false when rolling the dice so the user can't click it twice
        currentDiceValue = Random.nextInt(1,7)

        // Adjust index to match zero-based indexing of the array
        val index = currentDiceValue - 1

        // Set the tag of the ImageView to the current dice value
        binding.imageView.tag = currentDiceValue

        //set image views
        binding.imageView.setImageResource(diceIds[index])


        //When dice value is 1
        when(index + 1){
            //Addition
            1 -> {
                binding.updatetextView.text = "Solve This Addition Problem!"

                // Enable the answer input box and guess button
                binding.editText.visibility = View.VISIBLE
                binding.guessbutton.visibility = View.VISIBLE


                // Display a randomized addition problem
                val num1 = Random.nextInt(1, 100)
                val num2 = Random.nextInt(1, 100)
                val correctAnswer = num1 + num2

                binding.problemText.text = "$num1+$num2"
            }


            //Subtraction
            2 -> {
                binding.updatetextView.text = "Solve This Subtraction Problem!"

                // Enable the answer input box and guess button
                binding.editText.visibility = View.VISIBLE
                binding.guessbutton.visibility = View.VISIBLE


                // Display a randomized subtraction problem
                val num1 = Random.nextInt(1, 100)
                val num2 = Random.nextInt(1,num1)
                val correctAnswer = num1 - num2


                binding.problemText.text = "$num1-$num2"
            }


            //Multiplication
            3 -> {
                binding.updatetextView.text = "Solve This Multiplication Problem!"

                // Enable the answer input box and guess button
                binding.editText.visibility = View.VISIBLE
                binding.guessbutton.visibility = View.VISIBLE


                // Display a randomized multiplication problem
                val num1 = Random.nextInt(1, 21)
                val num2 = Random.nextInt(1, 21)
                val correctAnswer = num1 * num2

                binding.problemText.text = "$num1*$num2"


            }


            //Roll again if answer is correct, double the points
            4 -> {

                //roll again, get double points if you answer correctly
                rollDice()
                binding.updatetextView.text = "Rolling again, Double your points!"
                isDoublePoints = true

                // Reset UI and go to the next turn
                //resetUI()
            }


            //Lose a turn
            5 -> {
                // Reset UI and go to the next turn
                resetUI()
                binding.updatetextView.text = "Oh no! You lost a turn! Next Player's turn."
                return
            }


            //Try for Jackpot
            6 -> {
                //roll again, get jackpot points if you answer correctly
                rollDice()
                isJackpotPoints = true
                binding.updatetextView.text = "Trying for jackpot!"

                // Reset UI and go to the next turn
                //resetUI()
            }


        }

        // Re-enable guess button
        binding.guessbutton.isEnabled = true

    }

    //Function to update points based on the current turn
    private fun updatePoints() {
        // Update total points based on the current turn
        totalPoints1 += currentPoints1
        totalPoints2 += currentPoints2
        totalJackpoints += jackpoint

        // Update points display
        binding.player1View.text = "Player 1 total = $totalPoints1"
        binding.player2View.text = "Player 2 total = $totalPoints2"
        binding.jackpotView.text = "Current Jackpot = $jackpoint"

        // Reset current points at the beginning of each turn
        currentPoints1 = 0
        currentPoints2 = 0
        jackpoint = 5
    }


    //user clicks the guess button
    //user input is not the problem, its reading the problemText update: correct it was the trimming that was incorrect
    private fun checkAnswer() {
        val userAnswer = binding.editText.text.toString().trim()

        if (userAnswer.isNotEmpty()) {
            try {
                // Attempt to parse the user's answer
                val userAnswerInt = userAnswer.toInt()

                val multiplier = if (isDoublePoints) 2 else 1
                val getJackpot = if (isJackpotPoints) jackpoint else 1

                val correctAnswer: Int

                when (currentDiceValue) {
                    // Addition problem
                    1 -> {
                        val expression = binding.problemText.text.toString().replace("\\s".toRegex(), "")
                        val num1 = expression.substringBefore('+').toInt()
                        val num2 = expression.substringAfter('+').toInt()
                        correctAnswer = num1 + num2

                        if (userAnswerInt == correctAnswer) {
                            if (currentPlayer == 1)
                                currentPoints1 += 1 * multiplier
                            else
                                currentPoints2 += 1 * multiplier

                            binding.updatetextView.text = "Correct! Player $currentPlayer gets 1 point."

                            //This applies if user gets a jackpot, answering a question right (jackpot + original points)
                            //If user gets double points and rolls jackpot, this can still apply
                            if (isJackpotPoints == true){
                                if (currentPlayer == 1)
                                    currentPoints1 += getJackpot
                                else
                                    currentPoints2 += getJackpot
                            }

                        } else {
                            jackpoint += 1  * multiplier
                            binding.updatetextView.text = "Wrong answer! 1 point added to Jackpot."
                        }


                    }

                    // Subtraction problem
                    2 -> {
                        val expression = binding.problemText.text.toString().replace("\\s".toRegex(), "")
                        val num1 = expression.substringBefore('-').toInt()
                        val num2 = expression.substringAfter('-').toInt()
                        correctAnswer = num1 - num2

                        if (userAnswerInt == correctAnswer) {
                            if (currentPlayer == 1)
                                currentPoints1 += 2 * multiplier
                            else
                                currentPoints2 += 2 * multiplier

                            binding.updatetextView.text = "Correct! Player $currentPlayer gets 2 points."

                            //This applies if user gets a jackpot, answering a question right (jackpot + original points)
                            //If user gets double points and rolls jackpot, this can still apply
                            if (isJackpotPoints == true){
                                if (currentPlayer == 1)
                                    currentPoints1 += getJackpot
                                else
                                    currentPoints2 += getJackpot
                            }

                        } else {
                            jackpoint += 2 * multiplier
                            binding.updatetextView.text = "Wrong answer! 2 points added to Jackpot."
                        }

                    }

                    // Multiplication problem
                    3 -> {
                        val expression = binding.problemText.text.toString().replace("\\s".toRegex(), "")
                        val num1 = expression.substringBefore('*').toInt()
                        val num2 = expression.substringAfter('*').toInt()
                        correctAnswer = num1 * num2

                        if (userAnswerInt == correctAnswer) {
                            if (currentPlayer == 1)
                                currentPoints1 += 3 * multiplier
                            else
                                currentPoints2 += 3 * multiplier

                            binding.updatetextView.text = "Correct! Player $currentPlayer gets 3 points."

                            //This applies if user gets a jackpot, answering a question right (jackpot + original points)
                            //If user gets double points and rolls jackpot, this can still apply
                            if (isJackpotPoints == true){
                                if (currentPlayer == 1)
                                    currentPoints1 += getJackpot
                                else
                                    currentPoints2 += getJackpot
                            }

                        } else {
                            jackpoint += 3 * multiplier
                            binding.updatetextView.text = "Wrong answer! 3 points added to Jackpot."
                        }

                    }

                    else -> {
                        correctAnswer = 0
                    }
                }

            } catch (e: NumberFormatException) {
                binding.updatetextView.text = "Sorry, try inputting another answer!"
                e.printStackTrace()
            }

        } else {
            binding.updatetextView.text = "Please input an answer!"
        }

        // Update points for the current turn
        updatePoints()

        // Reset UI and go to the next turn
        resetUI()

    }


    private fun resetUI() {
        // Reset UI elements and go to the next player's turn
        binding.editText.visibility = View.GONE
        binding.guessbutton.isEnabled = false

        currentPlayer = if (currentPlayer == 1) 2 else 1

        binding.currentplayView.text = "Current Player = $currentPlayer"
        binding.updatetextView.text = " "

        isDoublePoints = false
        isJackpotPoints = false

        isAnswered = true

        if (totalPoints1 >= 20 || totalPoints2 >= 20) {
                // Game over
                binding.updatetextView.text = "Game Over! Player ${if (totalPoints1 >= 20) 1 else 2} wins!"
                binding.rolldiceButton.isEnabled = false
                binding.guessbutton.isEnabled = false

                // Reset total points when the game is restarted
                totalPoints1 = 0
                totalPoints2 = 0
                totalJackpoints = 5
        }



    }





}

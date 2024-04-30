Project Description
For the creation of Project 4, I developed a news-gathering app titled “News Now”. This app involves interaction with a web service, specifically a news API called NewsData.IO. NewsData.IO was used to supply information about different articles. This API supplies lots of news data so for simplicity the news gathered for this app relates to the most recent articles related to cryptocurrency, this can be modified with the API URL in the NewsViewModel.

News Now has the following components within its structure:
●	Article.kt
○	 the data class for the articles

●	MyApp.kt 
○	the project’s application class

●	NewsButtonFragment.kt 
○	A fragment for the button that will generate/fetch a random news article given from the NewsData.IO API
○	Once the button is clicked/tapped, it calls the fetchRandomArticle function from the NewsViewModel

●	NewsContentFragment.kt
○	Displays the fetched article/news content once the button is clicked/tapped
○	Images are loaded using Glide functionality
○	Any data not available upon generation will have a placeholder image/text

●	NewsViewModel.kt
○	Acts as a “middle man” for changes in data using LiveData, JSON parsing with Volley, and view model aspects
○	Contains the fetchRandomArticle function 

●	MainActivity.kt
○	Displays the fragments upon creation



Widgets/Views used:
●	Text views
●	Image views
●	Button
●	Divider
●	View
●	Scroll Views
●	Fragment Container Views


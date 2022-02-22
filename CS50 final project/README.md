# Avatartar_Sauce
#### Video Demo:  https://youtu.be/QV0pp-tdQUM
#### Description:
    This is a web application that allows users to create their own avatar as well as see the avatars other people have created in a gallery.

    With regards to the avatar creation and drawings, I used the py-avataaars library to help me generate all the characters and their features. This app uses python, SQL, HTML, CSS and Javascript with Flask as the web framework.

    Upon opening the web app or going to the link, you are greeted with a login page where the user has to register for an account and only then can he or she log in and proceed with the app.
    The username and hashed password is stored in a database, this allows for the user to log in again in future. When a user registers for account it will also insert data into another database which I created to store the user's avatar features. However, all the data inserted into that database is NULL as the user has not yet created his or her avatar.

    After the user has logged in, the user is redirected to the index page via get request. There will be a form for the user to fill out. This form will contain the features of the avatar that the user can change with the help of selection menus. I also included 2 new fields that allows the user to give the avatar a name and a catchphrase. The name will be shown above the avatar image and the catchphrase will be shown when the mouse hovers over the image. Once the user submits the form,  I redirect them to the same index.html page via get request and my code will take their responses and generate a png file of their avatar to my drive, I then move the png file to my static folder so that the img tag on my html page can find it and show the image. The src attribute of the img tag contains a variable which I will pass into it when I call the render_template function. That variable is the user id of the particular session which will allow the html page to only show the user's avatar image and not anyone elses'.
    This most recent png file of the avatar that was created would be called png file (2).
    and the previous png file (2) will be renamed to png file (1)

    The avatar features/traits that the user selected is also updated to the database that I mentioned eariler (containing all users' avatars' traits). This allows me to save their responses and pass it into my html templates such that when the get request is made via the redirect, the options shown on the form will not go back to its default options but instead remain as the options that the user previously selected, this allows for the user to easily choose the features that they want without them having to think about what they selected earlier.

    When the get request is made to my index.html, my code will also automatically delete png file (1). this helps to save memory in my drive so that i will only have the latest images of the avatars of my users, and hence, allow for more users in my app.

    at the bottom of the index page, there is a button that redirects the user to a gallery page such that the user will be able to see other users' avatars, names and catchphrases. This was made possible with the help of the database containing all the users' avatars' features that I can pass into the html page so as to generate the correct number of divs with the image, name and catchphrase inside. One div for each user.
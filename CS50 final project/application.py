import os
import py_avataaars as pa
import base64
import streamlit as st
import io
import shutil

from PIL import Image
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import login_required, apology

# API token: export API_KEY=pk_4674a339c5e94198a7d4ae55421a1529

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///avatartar_sauce.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

skin_color='default'
top_type='default'
hair_color='default'
facial_hair_type='default'
mouth_type='default'
eye_type='default'
eyebrow_type='default'
accessories_type='default'
clothe_type='default'
clothe_graphic_type='default'

@app.route("/", methods=["GET", "POST"])
@login_required
def create():
    if request.method == "POST":
        avatar=pa.PyAvataaar(
        style=pa.AvatarStyle.TRANSPARENT,
        skin_color=eval('pa.SkinColor.{}'.format(request.form.get('skin_color'))),
        top_type=eval('pa.TopType.{}'.format(request.form.get('top_type'))),
        hat_color=eval('pa.Color.{}'.format(request.form.get('hat_color'))),
        hair_color=eval('pa.HairColor.{}'.format(request.form.get('hair_color'))),
        facial_hair_type=eval('pa.FacialHairType.{}'.format(request.form.get('facial_hair_type'))),
        facial_hair_color=eval('pa.HairColor.{}'.format(request.form.get('facial_hair_color'))),
        mouth_type=eval('pa.MouthType.{}'.format(request.form.get('mouth_type'))),
        eye_type=eval('pa.EyesType.{}'.format(request.form.get('eye_type'))),
        eyebrow_type=eval('pa.EyebrowType.{}'.format(request.form.get('eyebrow_type'))),
        nose_type=pa.NoseType.DEFAULT,
        accessories_type=eval('pa.AccessoriesType.{}'.format(request.form.get('accessories_type'))),
        clothe_type=eval('pa.ClotheType.{}'.format(request.form.get('clothe_type'))),
        clothe_color=eval('pa.Color.{}'.format(request.form.get('clothe_color'))),
        clothe_graphic_type=eval('pa.ClotheGraphicType.{}'.format(request.form.get('clothe_graphic_type')))
        )

        db.execute("UPDATE avatar_traits SET avatar_name= ?, skin_color=?, top_type=?, hair_color=?, facial_hair_type=?, mouth_type=?, eye_type=?, eyebrow_type=?, accessories_type=?, clothe_type=?, clothe_graphic_type=?, catchphrase=?, hat_color=?, facial_hair_color=?, clothe_color=? WHERE id=?;"
        , request.form.get('avatar_name'), request.form.get('skin_color'), request.form.get('top_type'), request.form.get('hair_color'), request.form.get('facial_hair_type'), request.form.get('mouth_type'), request.form.get('eye_type'), request.form.get('eyebrow_type')
        , request.form.get('accessories_type'), request.form.get('clothe_type'), request.form.get('clothe_graphic_type'), request.form.get('catchphrase'), request.form.get('hat_color'), request.form.get('facial_hair_color'), request.form.get('clothe_color'), session['user_id'])

        # storing the selected options in global variables


        # rename the old png file to (1)
        if os.path.exists('/home/ubuntu/project/static/output_{}_2.png'.format(session['user_id'])):
            os.rename('/home/ubuntu/project/static/output_{}_2.png'.format(session['user_id']), '/home/ubuntu/project/static/output_{}_1.png'.format(session['user_id']))

        else:
            print('png file (2) not found')


        # rendering avatar png (2) and then moving it to my static folder
        avatar.render_png_file('output_{}_2.png'.format(session['user_id']))
        shutil.move('output_{}_2.png'.format(session['user_id']), 'static')

        return redirect('/')

    else:
        # include a list of the available options in the html page
        list_skin_color = ['TANNED','YELLOW','PALE','LIGHT','BROWN','DARK_BROWN','BLACK']
        list_top_type = ['NO_HAIR','EYE_PATCH','HAT','HIJAB','TURBAN',
                 'WINTER_HAT1','WINTER_HAT2','WINTER_HAT3',
                 'WINTER_HAT4','LONG_HAIR_BIG_HAIR','LONG_HAIR_BOB',
                 'LONG_HAIR_BUN','LONG_HAIR_CURLY','LONG_HAIR_CURVY',
                 'LONG_HAIR_DREADS','LONG_HAIR_FRIDA','LONG_HAIR_FRO',
                 'LONG_HAIR_FRO_BAND','LONG_HAIR_NOT_TOO_LONG',
                 'LONG_HAIR_SHAVED_SIDES','LONG_HAIR_MIA_WALLACE',
                 'LONG_HAIR_STRAIGHT','LONG_HAIR_STRAIGHT2',
                 'LONG_HAIR_STRAIGHT_STRAND','SHORT_HAIR_DREADS_01',
                 'SHORT_HAIR_DREADS_02','SHORT_HAIR_FRIZZLE',
                 'SHORT_HAIR_SHAGGY_MULLET','SHORT_HAIR_SHORT_CURLY',
                 'SHORT_HAIR_SHORT_FLAT','SHORT_HAIR_SHORT_ROUND',
                 'SHORT_HAIR_SHORT_WAVED','SHORT_HAIR_SIDES',
                 'SHORT_HAIR_THE_CAESAR','SHORT_HAIR_THE_CAESAR_SIDE_PART']
        list_hair_color = ['AUBURN','BLACK','BLONDE','BLONDE_GOLDEN','BROWN',
                   'BROWN_DARK','PASTEL_PINK','PLATINUM','RED','SILVER_GRAY']
        list_hat_color = ['BLACK','BLUE_01','BLUE_02','BLUE_03','GRAY_01','GRAY_02',
                  'HEATHER','PASTEL_BLUE','PASTEL_GREEN','PASTEL_ORANGE',
                  'PASTEL_RED','PASTEL_YELLOW','PINK','RED','WHITE']
        list_facial_hair_type = ['DEFAULT','BEARD_MEDIUM','BEARD_LIGHT','BEARD_MAJESTIC','MOUSTACHE_FANCY','MOUSTACHE_MAGNUM']
        list_facial_hair_color = ['AUBURN','BLACK','BLONDE','BLONDE_GOLDEN','BROWN','BROWN_DARK','PLATINUM','RED']
        list_mouth_type = ['DEFAULT','CONCERNED','DISBELIEF','EATING','GRIMACE','SAD','SCREAM_OPEN','SERIOUS','SMILE','TONGUE','TWINKLE','VOMIT']
        list_eye_type = ['DEFAULT','CLOSE','CRY','DIZZY','EYE_ROLL','HAPPY','HEARTS','SIDE','SQUINT','SURPRISED','WINK','WINK_WACKY']
        list_eyebrow_type = ['DEFAULT','DEFAULT_NATURAL','ANGRY','ANGRY_NATURAL','FLAT_NATURAL','RAISED_EXCITED','RAISED_EXCITED_NATURAL','SAD_CONCERNED','SAD_CONCERNED_NATURAL','UNI_BROW_NATURAL','UP_DOWN','UP_DOWN_NATURAL','FROWN_NATURAL']
        list_accessories_type = ['DEFAULT','KURT','PRESCRIPTION_01','PRESCRIPTION_02','ROUND','SUNGLASSES','WAYFARERS']
        list_clothe_type = ['BLAZER_SHIRT','BLAZER_SWEATER','COLLAR_SWEATER','GRAPHIC_SHIRT','HOODIE','OVERALL','SHIRT_CREW_NECK','SHIRT_SCOOP_NECK','SHIRT_V_NECK']
        list_clothe_color = ['BLACK','BLUE_01','BLUE_02','BLUE_03','GRAY_01','GRAY_02','HEATHER','PASTEL_BLUE','PASTEL_GREEN','PASTEL_ORANGE','PASTEL_RED','PASTEL_YELLOW','PINK','RED','WHITE']
        list_clothe_graphic_type = ['BAT','CUMBIA','DEER','DIAMOND','HOLA','PIZZA','RESIST','SELENA','BEAR','SKULL_OUTLINE','SKULL']


        # delete the previous png file, keep the most updated one
        if os.path.exists('/home/ubuntu/project/static/output_{}_1.png'.format(session['user_id'])):
            os.remove('/home/ubuntu/project/static/output_{}_1.png'.format(session['user_id']))
        else:
            print('png file (1) not found')

        # store the png file name in a variable and pass it into the template so that it can find the png file
        if os.path.exists('/home/ubuntu/project/static/output_{}_2.png'.format(session['user_id'])):
            image = 'output_{}_2.png'.format(session['user_id'])
            print('image2 found')

        else:
            image = 'null'

        # select from database the previous inputs to the most recent avatar
        avatar_traits = db.execute('SELECT avatar_name, skin_color, top_type, hair_color, facial_hair_type, mouth_type, eye_type, eyebrow_type, accessories_type, clothe_type, clothe_graphic_type, catchphrase, hat_color, facial_hair_color, clothe_color FROM avatar_traits WHERE id=?;', session['user_id'])

        avatar_name = avatar_traits[0]['avatar_name']
        skin_color = avatar_traits[0]['skin_color']
        top_type = avatar_traits[0]['top_type']
        hair_color = avatar_traits[0]['hair_color']
        facial_hair_type = avatar_traits[0]['facial_hair_type']
        mouth_type = avatar_traits[0]['mouth_type']
        eye_type = avatar_traits[0]['eye_type']
        eyebrow_type = avatar_traits[0]['eyebrow_type']
        accessories_type = avatar_traits[0]['accessories_type']
        clothe_type = avatar_traits[0]['clothe_type']
        clothe_graphic_type = avatar_traits[0]['clothe_graphic_type']
        catchphrase = avatar_traits[0]['catchphrase']
        hat_color = avatar_traits[0]['hat_color']
        facial_hair_color = avatar_traits[0]['facial_hair_color']
        clothe_color = avatar_traits[0]['clothe_color']

        return render_template('index.html', list_skin_color=list_skin_color, list_top_type=list_top_type, list_hair_color=list_hair_color, list_hat_color=list_hat_color,
        list_facial_hair_type=list_facial_hair_type, list_facial_hair_color=list_facial_hair_color, list_mouth_type=list_mouth_type, list_eye_type=list_eye_type, list_eyebrow_type=list_eyebrow_type,
        list_accessories_type=list_accessories_type, list_clothe_type=list_clothe_type, list_clothe_color=list_clothe_color, list_clothe_graphic_type=list_clothe_graphic_type, image=image, skin_color=skin_color,
        top_type=top_type, hair_color=hair_color, facial_hair_type=facial_hair_type, mouth_type=mouth_type, eye_type=eye_type, eyebrow_type=eyebrow_type, accessories_type=accessories_type,
        clothe_type=clothe_type, clothe_graphic_type=clothe_graphic_type, avatar_name=avatar_name, catchphrase=catchphrase, hat_color=hat_color, facial_hair_color=facial_hair_color, clothe_color=clothe_color
        )

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM players WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # if registration form is submitted
    if request.method == "POST":
        # ensure usrname is submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get('confirmation'):
            return apology("must provide password")

        # check if username already exists
        new_username = db.execute('SELECT * FROM players WHERE username = ?', request.form.get("username"))
        print(new_username)
        if len(new_username) != 0:
            return apology('username taken')

        # check if passwords match
        if request.form.get("password") != request.form.get('confirmation'):
            return apology('password and confirmation do not match')

        # now that all restrictions were passed, add the user to the user table
            # hash the password to be stored into the database. each time u hash may result in a diff output but it will still be accounted for in the check hash function
        h_password = generate_password_hash(request.form.get("password"))
        db.execute('INSERT INTO players (username, hash) VALUES (?, ?)', request.form.get("username"), h_password)
        new_user_id = db.execute('SELECT id FROM players WHERE username = ?', request.form.get("username"))
        user_id = new_user_id[0]['id']
        db.execute('INSERT INTO avatar_traits (id, avatar_name, skin_color, top_type, hair_color, facial_hair_type, mouth_type, eye_type, eyebrow_type, accessories_type, clothe_type, clothe_graphic_type, catchphrase, hat_color, facial_hair_color, clothe_color) VALUES (?, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)'
        , user_id)
        return redirect("/")

    else:
        return render_template('register.html')

@app.route("/gallery")
@login_required
def gallery():
    avatar_data = db.execute('SELECT avatar_name, skin_color, top_type, hair_color, facial_hair_type, mouth_type, eye_type, eyebrow_type, accessories_type, clothe_type, clothe_graphic_type, catchphrase, hat_color, facial_hair_color, clothe_color FROM avatar_traits;')
    n = len(avatar_data)
    return render_template('gallery.html', avatar_data=avatar_data, n=n)
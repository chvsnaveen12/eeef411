# render.py
from flask import Flask, render_template

app = Flask(__name__)       # Initialize a Flask object

@app.route('/user/<user_name>')   # All the URLs will be routed here
def render(user_name):       # This function will be executes whenever an API request is made.
    return render_template('render.html', name = user_name)   # Returns the webpage 

# Start the app at port 5000, and make it visible to outside networks
app.run(host = '0.0.0.0', port=5000)

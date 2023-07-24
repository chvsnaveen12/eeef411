# first.py# submit.py
from flask import Flask

app = Flask(__name__)       # Initialize a Flask object

# Take a float input called temp_c
@app.route('/CtoF/<float:temp_c>') 
def CtoF(temp_c):     # This function will be executes whenever an API request is made.
    temp_f = float((temp_c*1.8) + 32)   # Perform the conversion
    # Return the data in a JSON format
    return {"temp": temp_c, "temp_f": temp_f}
   
# Take a float input called temp_f
@app.route('/FtoC/<float:temp_f>') 
def FtoC(temp_f):     # This function will be executes whenever an API request is made.
    temp_c = float((temp_f - 32)/1.8)   # Perform the conversion
    # Return the data in a JSON format
    return {"temp": temp_c, "temp_f": temp_f}

# Start the app at port 5000, and make it visible to outside networks
app.run(host = '0.0.0.0', port=5000)
from flask import Flask

app = Flask(__name__)       # Initialize a Flask object

@app.route('/')             # All the URLs will be routed here
def hello_world():          # This function will be executes whenever an API request is made.
    return 'Hello World!'   # Returns a simple hello world message 

# Start the app at port 5000, and make it visible to outside networks
app.run(host = '0.0.0.0', port=5000)

from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)


    positive, negative, neutral = set_score(tweets)

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)

def set_score(tweets):
    # instantiate analyzer
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives)
    # tokenize tweets
    tokens = [helpers.tokenize(i) for i in tweets]
    positive, negative, neutral = 0.0, 0.0, 0.0
    for tweet in tokens:
        score = 0
        for word in tweet:
            score += analyzer.analyze(word)
        if score > 0:
            positive += 1
        elif score < 0:
            negative += 1
        else:
            neutral += 1
    positive = positive * 100 / len(tweets)
    negative = negative * 100 / len(tweets)
    neutral = 100 - (positive + negative)
    return positive, negative, neutral

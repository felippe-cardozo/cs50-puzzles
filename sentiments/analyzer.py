import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = self.load(positives)
        self.negatives = self.load(negatives)

    def analyze(self, word):
        """Analyze text for sentiment, returning its score."""
        # tokens = self.tokenize(text)
        if word in self.positives:
            return 1
        if word in self.negatives:
            return -1
        return 0


    def tokenize(self, text):
        tokenizer = nltk.tokenize.TweetTokenizer()
        return tokenizer.tokenize(text)

    def load(self, _file):
        load = set()
        f = open(_file, "r")
        for line in f:
            line = line.strip()
            if line.startswith(";") or not line.strip():
                continue
            load.add(line)
        f.close()
        return load


'use strict'

const fs = require('fs');
const os = require('os');
const path = require('path');
const bench = require('fastbench');
const tfIdf = require('./tfidf');
const RecommenderSystem = require('../dist/binding.js');

const documentsFilePath = path.join(__dirname, 'documents.txt')
const termsFilePath = path.join(__dirname, 'terms.txt');
const documents = fs.readFileSync(documentsFilePath).toString();
const terms = fs.readFileSync(termsFilePath).toString().split(os.EOL);
const instance = new RecommenderSystem();

const run = bench([
    function vanillaJS(done) {
        tfIdf(documents, terms);
        done();
    },
    function nativeAddon(done) {
        instance.tfIdf(documentsFilePath, termsFilePath);
        done();
    },
], 1000);

run(run);
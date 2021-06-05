'use strict'

const fs = require('fs');
const os = require('os');
const path = require('path');
const bench = require('fastbench');
const tfIdf = require('./tfidf');
const NodeRankFns = require('../dist/binding.js');

const documentsFilePath = path.join(__dirname, 'documents.txt')
const termsFilePath = path.join(__dirname, 'terms.txt');
const documents = fs.readFileSync(documentsFilePath).toString();
const terms = fs.readFileSync(termsFilePath).toString().split(os.EOL);
const rankFns = new NodeRankFns();

const run = bench([
    function vanillaJS(done) {
        tfIdf(documents, terms);
        done();
    },
    function nativeAddon(done) {
        rankFns.tfIdf(documentsFilePath, termsFilePath, done);
    },
], 1000);

run(run);
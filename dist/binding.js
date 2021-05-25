"use strict";
const addon = require('../build/Release/recommender-system');
class RecommenderSystem {
    constructor() {
        this._addonInstance = new addon.RecommenderSystem();
    }
    tfIdf(documents, terms) {
        return this._addonInstance.tfIdf(documents, terms);
    }
    bm25(documents, terms) {
        return this._addonInstance.bm25(documents, terms);
    }
}
module.exports = RecommenderSystem;

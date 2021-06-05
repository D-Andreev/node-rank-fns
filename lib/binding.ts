const addon = require('../build/Release/recommender-system');

interface IRecommenderSystemNative {
    tfIdf(documents: string[], terms: string[], callback: Function): string[];
    bm25(documents: string[], terms: string[], callback: Function): string[];
}

class RecommenderSystem {
    constructor() {
        this._addonInstance = new addon.RecommenderSystem();
    }

    tfIdf(documents: string[], terms: string[], callback: Function): string[] {
        return this._addonInstance.tfIdf(documents, terms, callback);
    }

    bm25(documents: string[], terms: string[], callback: Function): string[] {
        return this._addonInstance.bm25(documents, terms, callback);
    }

    // private members
    private _addonInstance: IRecommenderSystemNative;
}

export = RecommenderSystem;

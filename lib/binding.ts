const addon = require('../build/Release/recommender-system');

interface IRecommenderSystemNative {
    tfIdf(documents: string[], terms: string[]): string[];
    bm25(documents: string[], terms: string[]): string[];
}

class RecommenderSystem {
    constructor() {
        this._addonInstance = new addon.RecommenderSystem();
    }

    tfIdf(documents: string[], terms: string[]): string[] {
        return this._addonInstance.tfIdf(documents, terms);
    }

    bm25(documents: string[], terms: string[]): string[] {
        return this._addonInstance.bm25(documents, terms);
    }

    // private members
    private _addonInstance: IRecommenderSystemNative;
}

export = RecommenderSystem;

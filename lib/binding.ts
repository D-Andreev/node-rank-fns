const addon = require('../build/Release/node-rank-fns');

interface INodeRankFnsNative {
    tfIdf(documents: string[], terms: string[], callback: Function): string[];
    bm25(documents: string[], terms: string[], callback: Function): string[];
}

class NodeRankFns {
    constructor() {
        this._addonInstance = new addon.NodeRankFns();
    }

    tfIdf(documents: string[], terms: string[], callback: Function): string[] {
        return this._addonInstance.tfIdf(documents, terms, callback);
    }

    bm25(documents: string[], terms: string[], callback: Function): string[] {
        return this._addonInstance.bm25(documents, terms, callback);
    }

    // private members
    private _addonInstance: INodeRankFnsNative;
}

export = NodeRankFns;

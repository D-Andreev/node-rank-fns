const addon = require('../build/Release/node-rank-fns');

interface INodeRankFnsNative {
    tfIdf(documents: string, terms: string, callback: Function): number[];
    bm25(documents: string, terms: string, callback: Function): number[];
}

interface IOptions {
    k?: number;
    b?: number;
}

class NodeRankFns {
    constructor(options?: IOptions) {
        this._addonInstance = new addon.NodeRankFns(options);
    }

    tfIdf(documents: string, terms: string, callback: Function): number[] {
        return this._addonInstance.tfIdf(documents, terms, callback);
    }

    bm25(documents: string, terms: string, callback: Function): number[] {
        return this._addonInstance.bm25(documents, terms, callback);
    }

    // private members
    private _addonInstance: INodeRankFnsNative;
}

export = NodeRankFns;

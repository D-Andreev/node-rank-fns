const addon = require('../build/Release/node-rank-fns');

interface INodeRankFnsNative {
    tfIdf(documents: string[], terms: string[]): string[];
}

class NodeRankFns {
    constructor() {
        this._addonInstance = new addon.NodeRankFns();
    }

    tfIdf(documents: string[], terms: string[]): string[] {
        return this._addonInstance.tfIdf(documents, terms);
    }

    // private members
    private _addonInstance: INodeRankFnsNative;
}

export = NodeRankFns;

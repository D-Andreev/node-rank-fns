const addon = require('../build/Release/node-rank-fns-native');

interface INodeRankFnsNative
{
    greet(strName: string): string;
};

class NodeRankFns {
    constructor(name: string) {
        this._addonInstance = new addon.NodeRankFns(name)
    }

    greet (strName: string) {
        return this._addonInstance.greet(strName);
    }

    // private members
    private _addonInstance: INodeRankFnsNative;
}

export = NodeRankFns;

interface IOptions {
    k?: number;
    b?: number;
}
declare class NodeRankFns {
    constructor(options?: IOptions);
    tfIdf(documents: string, terms: string, callback: Function): number[];
    bm25(documents: string, terms: string, callback: Function): number[];
    private _addonInstance;
}
export = NodeRankFns;

declare class RecommenderSystem {
    constructor();
    tfIdf(documents: string[], terms: string[], callback: Function): string[];
    bm25(documents: string[], terms: string[], callback: Function): string[];
    private _addonInstance;
}
export = RecommenderSystem;

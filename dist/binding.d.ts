declare class RecommenderSystem {
    constructor();
    tfIdf(documents: string[], terms: string[]): string[];
    bm25(documents: string[], terms: string[]): string[];
    private _addonInstance;
}
export = RecommenderSystem;

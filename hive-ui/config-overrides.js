// Original file https://github.com/rjwats/esp8266-react/blob/master/interface/config-overrides.js
// Thanks to the rightful author

const ManifestPlugin = require("webpack-manifest-plugin");
const WorkboxWebpackPlugin = require("workbox-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = function override(config, env) {
    if (env === "production") {
        // rename the ouput file, we need it's path to be short, for embedded FS
        config.output.filename = "js/[id].[chunkhash:4].js";
        config.output.chunkFilename = "js/[id].[chunkhash:4].js";

        // take out the manifest and service worker plugins
        config.plugins = config.plugins.filter(
            (plugin) => !(plugin instanceof ManifestPlugin)
        );
        config.plugins = config.plugins.filter(
            (plugin) => !(plugin instanceof WorkboxWebpackPlugin.GenerateSW)
        );

        // shorten css filenames
        const miniCssExtractPlugin = config.plugins.find(
            (plugin) => plugin instanceof MiniCssExtractPlugin
        );
        miniCssExtractPlugin.options.filename = "css/[id].[contenthash:4].css";
        miniCssExtractPlugin.options.chunkFilename = "css/[id].[contenthash:4].c.css";
    }
    return config;
};

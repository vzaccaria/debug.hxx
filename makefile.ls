#!/usr/bin/env lsc

{ parse, add-plugin } = require('newmake')

parse ->

    @add-plugin 'clang',(g, deps) ->
        @compile-files( (-> "clang++ -c --std=c++11 #{it.orig-complete} -I. -o #{it.build-target}"), ".o", g, deps )

    @add-plugin 'link', (files) ->
        @reduce-files( ("clang++ $^ -o $@"), "linked", "x", files)

    @collect "build", ->
        @dest "./bin/test", ->
            @link ->  [
                         @clang 'deps/*/**.cpp', 'deps/*/**.{hxx}'
                         @clang 'test/*.cpp', '*.hxx'
                         ]

    @collect "all", ->
        @command-seq -> [
            @make "build"
            ]

    @collect "clean", -> [
        @remove-all-targets()
        ]



        # @dest "./bin/frontend", ->
        #


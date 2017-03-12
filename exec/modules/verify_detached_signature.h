/*
verify_detached_signature.h
OpenPGP exectuable module

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __COMMAND_VERIFY_DETACHED_SIGNATURE__
#define __COMMAND_VERIFY_DETACHED_SIGNATURE__

#include "../../OpenPGP.h"
#include "module.h"

namespace module {

const Module verify_detached_signature(
    // name
    "verify-detached-signature",

    // positional arguments
    {
        "key",
        "file",
        "signature",
    },

    // optional arguments
    {

    },

    // optional flags
    {

    },

    // function to run
    [](const std::map <std::string, std::string> & args,
       const std::map <std::string, bool>        & flags) -> int {
        std::ifstream key(args.at("key"), std::ios::binary);
        if (!key){
            std::cerr << "Error: Public key file \"" + args.at("key") + "\" not opened." << std::endl;
            return -1;
        }

        std::ifstream file(args.at("file"), std::ios::binary);
        if (!file){
            std::cerr << "Error: Data file \"" + args.at("file") + "\" not opened." << std::endl;
            return -1;
        }

        std::ifstream sig(args.at("signature"), std::ios::binary);
        if (!sig){
            std::cerr << "Error: Signature file \"" + args.at("signature") + "\" not opened." << std::endl;
            return -1;
        }

        PGPKey signer(key);
        PGPDetachedSignature signature(sig);

        std::string error;
        const int verified = ::verify_detached_signature(signer, std::string(std::istreambuf_iterator <char> (file), {}), signature, error);

        if (verified == -1){
            std::cerr << error << std::endl;
        }
        else{
            std::cout << "File \"" << args.at("file") << "\" was" << ((verified == 1)?"":" not") << " signed by \"" << args.at("key") << "\" (" << signer << ")." << std::endl;
        }

        return 0;
    }
);

}

#endif
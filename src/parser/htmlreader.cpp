#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "htmlreader.h"
#include "textnode.h"
#include "document.h"

HTMLReader::HTMLReader()
{
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

void HTMLReader::parseDocumentText(std::string documentText)
{
    parseState currentState = initialMode;

    webpage = new Document;

    std::string::iterator i = documentText.begin();
    for (; i != documentText.end(); i++)
    {
        if (currentState == initialMode)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
        else if (currentState == tagOpen)
        {
            if (*i == '/')
            {
                currentState = endTagName;
            }
            else if (*i == '?')
            {
                currentState = bogusComment;
            }
            else if (*i == '!')
            {
                currentState = doctypeDeclaration;
            }
            else if (isalpha(*i))
            {
                i--;
                currentState = tagName;
            }
        }
        else if (currentState == tagName)
        {
            std::string tagNameString;
            while (currentState == tagName)
            {

                tagNameString.push_back(*i);

                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }

                if (*i == ' ')
                {
                    currentState = endTagName;
                }
            }

            if (tagNameString == "p")
            {
                currentState = text;
                std::string textString;
                while (currentState == text)
                {
                    i++;
                    if (*i == '<')
                    {
                        i--;
                        currentState = tagOpen;
                    }
                    else
                    {
                        textString.push_back(*i);
                    }
                }
                TextNode *textNode = new TextNode;
                textNode->setText(textString);
                webpage->constructTree(textNode);
            }

            //std::cout << tagNameString << std::endl;
        }
        else if (currentState == endTagName)
        {
            while (currentState == endTagName)
            {
                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }
            }
        }
        else if (currentState == endTagOpen)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
        else if (currentState == doctypeDeclaration)
        {
            while (currentState == doctypeDeclaration)
            {
                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }
            }
        }
        else if (currentState == text)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
    }
}

void HTMLReader::prepareDocument(std::string HTMLFilepath)
{
    try
    {
        std::ifstream HTMLDocument(HTMLFilepath.c_str());
        if (!HTMLDocument.is_open())
        {
            throw "Error: Could not open document.";
        }

        std::string documentText;
        std::string temporaryString;

        while (!HTMLDocument.eof())
        {
            std::getline(HTMLDocument, temporaryString);
            if (!documentText.empty())
            {
                documentText = documentText + "\n" + temporaryString;
            }
            else
            {
                documentText = temporaryString;
            }
        }

        HTMLDocument.close();

        parseDocumentText(documentText);

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}

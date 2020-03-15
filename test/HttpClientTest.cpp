//
// Created by MINE on 15/03/2020.
//

#include "dependency/catch.hpp"
#include <HttpClient.h>
#include <QApplication>


SCENARIO("Http Client Library With Basic Operations")
{

    QString url("https://httpbin.org/anything");
    HttpClient httpClient;
    GIVEN("Http Client to perform get Requests")
    {

        WHEN("The http request options is null")
        {
            THEN("should be success")
            {
                auto reply = httpClient.get(url, nullptr);
                REQUIRE(reply->statusCode() == 200);
            }
        }

        WHEN("The HttpRequest is initialized")
        {
            THEN("should be success")
            {
                HttpRequest req;
                auto reply = httpClient.get(url, &req);
                REQUIRE(reply->statusCode() == 200);
            }
        }
    }

    GIVEN("Http Client to perform post requests")
    {
        WHEN("The http request options is null")
        {
            THEN("Should be success")
            {
                auto reply = httpClient.post(url, nullptr);
                REQUIRE(reply->statusCode() == 200);
            }
        }

        WHEN("The http request option is initialized")
        {
            THEN("Should be success")
            {
                HttpRequest httpRequest;
                QObject::connect(&httpClient, &HttpClient::beforeRequest, [](const HttpRequest* request) {
                    REQUIRE(request->timeout() == 3000);
                });
                httpRequest.setTimeout(3000);
                auto reply = httpClient.post(url, &httpRequest);
                REQUIRE(reply->statusCode() == 200);
            }
        }
    }

    GIVEN("Http Client to perform put requests")
    {
        WHEN("The http request options is null")
        {
            THEN("Should be success")
            {
                auto reply = httpClient.put(url, nullptr);
                REQUIRE(reply->statusCode() == 200);
            }
        }

        WHEN("The http request option is initialized")
        {
            THEN("Should be success")
            {
                HttpRequest httpRequest;
                QObject::connect(&httpClient, &HttpClient::beforeRequest, [](const HttpRequest* request) {
                    REQUIRE(request->timeout() == 3000);
                });
                httpRequest.setTimeout(3000);
                auto reply = httpClient.put(url, &httpRequest);
                REQUIRE(reply->statusCode() == 200);
            }
        }
    }

    GIVEN("Http Client to perform patch requests")
    {
        WHEN("The http request options is null")
        {
            THEN("Should be success")
            {
                auto reply = httpClient.patch(url, nullptr);
                REQUIRE(reply->statusCode() == 200);
            }
        }

        WHEN("The http request option is initialized")
        {
            THEN("Should be success")
            {
                HttpRequest httpRequest;
                QObject::connect(&httpClient, &HttpClient::beforeRequest, [](const HttpRequest* request) {
                    REQUIRE(request->timeout() == 3000);
                });
                httpRequest.setTimeout(3000);
                auto reply = httpClient.patch(url, &httpRequest);
                REQUIRE(reply->statusCode() == 200);
            }
        }
    }

    GIVEN("Http Client to perform delete requests")
    {
        WHEN("The http request options is null")
        {
            THEN("Should be success")
            {
                auto reply = httpClient.del(url, nullptr);
                REQUIRE(reply->statusCode() == 200);
            }
        }

        WHEN("The http request option is initialized")
        {
            THEN("Should be success")
            {
                HttpRequest httpRequest;
                QObject::connect(&httpClient, &HttpClient::beforeRequest, [](const HttpRequest* request) {
                    REQUIRE(request->timeout() == 3000);
                });
                httpRequest.setTimeout(3000);
                auto reply = httpClient.del(url, &httpRequest);
                REQUIRE(reply->statusCode() == 200);
            }
        }
    }
}


SCENARIO("Http Client Library With Proxy")
{
    HttpClient httpClient;
    QString url = "https://httpbin.org/ip";
    GIVEN("HttpClient to perform http request with proxy")
    {
        WHEN("proxy is null")
        {
            THEN("return current IP")
            {
                auto reply = httpClient.get(url, nullptr);
                REQUIRE((!reply->json()["origin"].isNull()));
            }
        }

        WHEN("proxy is provided")
        {
            HttpRequest request;
            QNetworkProxy networkProxy;
            QString proxyIP = "50.246.120.125";
            networkProxy.setHostName(proxyIP);
            networkProxy.setPort(8080);
            request.setProxy(&networkProxy);
            auto reply = httpClient.get(url, &request);
            auto ipAfterProxy = reply->json()["origin"].toString();
            REQUIRE(!ipAfterProxy.isEmpty());
            REQUIRE(proxyIP == ipAfterProxy);
        }

    }
}
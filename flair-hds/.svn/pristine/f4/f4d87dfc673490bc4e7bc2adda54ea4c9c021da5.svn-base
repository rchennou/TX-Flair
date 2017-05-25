/*!
 * \file StreamingFilter.h
 * \brief StreamingFilter image flow over socket
 * \author Thomas Fuhrmann, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/01/26
 * \version 1.0
 */


#ifndef STREAMING_FILTER_H
#define STREAMING_FILTER_H

#include <IODevice.h>

namespace flair {
    namespace core {
        class TcpSocket;
        class cvimage;
    }
}

namespace flair {
    namespace filter {
        /*! \class StreamingFilter
        *
        * \brief StreamingFilter image flow over socket
        *
        */
        class StreamingFilter : public core::IODevice {
        public:

            StreamingFilter(const core::IODevice *parent, std::string name, std::string ipAddress, int ipPort);

            /*!
            * \brief Destructor
            *
            */
            ~StreamingFilter();

        private:
            /*!
            * \brief Update using provided datas
            *
            * Reimplemented from IODevice.
            *
            * \param data data from the parent to process
            */
            void UpdateFrom(const core::io_data *data);

            core::cvimage *output;

            //socket stuff
            core::TcpSocket *sendingSocket;

            bool suspendFlag;
        };
    } // end namespace filter
} // end namespace flair
#endif // STREAMING_FILTER_H
